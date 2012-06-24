<?php


/**
 * DownfallMigration
 */

abstract class DownfallMigration extends Migration {
  public function __construct() {
    // Always call the parent constructor first for basic setup
    parent::__construct(MigrateGroup::getInstance('downfall', array('default')));

    $this->team = array(
      new MigrateTeamMember('Chris Bloom', 'bloomcb@gmail.com', t('Guild Site Runner')),
    );
  }

  // make lowercase, space removed machine names
  public function vocabMachineName($args){
    return preg_replace('@[^a-z0-9_]+@','_',strtolower($args));
  }
}

/*
 * Vocabs
 */
class DownfallVocabularyMigration extends DownfallMigration {
  public function __construct() {
    parent::__construct();

    $this->description = t('Migrate taxonomies from d6 to d7.');

    $table_name = 'taxonomy_vocabulary'; //gets used a few times

    $this->map = new MigrateSQLMap(
      $this->machineName,
      array(
        'vid' => array(
          'type' => 'int',
          'length' => 10,
          'not null' => FALSE,
          'description' => '',
        )
      ),
      //built in from migrate to map drupal terms automatically
      MigrateDestinationTable::getKeySchema($table_name)
    );

    $query = Database::getConnection('migrate', 'df6import')
           ->select('vocabulary', 'vocab')
           ->fields('vocab', array('vid', 'name', 'description', 'module', 'weight'));

    // Create a MigrateSource object, which manages retrieving the input data.
    $this->source = new MigrateSourceSQL($query, array(), NULL, array('map_joinable' => FALSE));

    // Set up our destination using a generic table since there is none prebuilt for full vocabs
    $this->destination = new MigrateDestinationTable($table_name);

    $this->addSimpleMappings(array('name', 'description', 'module', 'weight'));
    $this->addFieldMapping('hierarchy')
         ->defaultValue(0);
    //maps to destination with modification to source, see function below
    $this->addFieldMapping('machine_name', 'name')
         ->callbacks(array($this, 'vocabMachineName')); // part of parent class
    //map unused source, usually do this for primary keys
    $this->addFieldMapping(NULL, 'vid')
         ->issueGroup(t('DNM'));
    $this->addUnmigratedDestinations(array('vid'));
  }

}

/**
 * Terms
 */
class DownfallTermWowMigration extends DownfallMigration {
  public function __construct() {
    parent::__construct();

    $this->description = t('Migrate terms from d6 to d7.');

    $this->dependencies = array('DownfallVocabulary');

    $this->map = new MigrateSQLMap($this->machineName,
      array(
        'tid' => array('type' => 'int',
                         'length' => 10,
                         'not null' => FALSE,
                         'description' => '',
                        )
      ),
      //built in from migrate to map drupal terms automatically
      MigrateDestinationTerm::getKeySchema()
    );


    $query = Database::getConnection('migrate', 'df6import')
           ->select('term_data', 'td')
           ->fields('td', array('tid', 'vid', 'name', 'description', 'weight'));
    $query->join('term_hierarchy', 'th', 'th.tid = td.tid');
    $query->addField('th', 'parent');
    //$query->groupBy('td.vid');
    $query->orderBy('td.vid, th.parent');

    //saving to get at this later
    $this->termsQuery = $query;

    // Create a MigrateSource object, which manages retrieving the input data.
    $this->source = new MigrateSourceSQL($query, array(), NULL, array('map_joinable' => FALSE));

    // Set up our destination - terms in the migrate_example_beer_styles vocabulary
    $this->destination = new MigrateDestinationTerm('wow'); // this doesn't really matter below

    // Assign mappings TO destination fields FROM source fields. To discover
    // the names used in these calls, use the drush commands
    // drush migrate-fields-destination BeerTerm
    // drush migrate-fields-source BeerTerm

    // this ensures that vids from d6 line up with their new vids in new d7
    $this->addFieldMapping('vid', 'vid')
         ->sourceMigration('DownfallVocabulary');

    // 'parent' is something built into Migrate
    $this->addFieldMapping('parent', 'parent')
         ->sourceMigration($this->machineName);

    $this->addSimpleMappings(array('name', 'description', 'weight'));

    // We conditionally DNM these fields, so your field mappings will be clean
    // whether or not you have path and or pathauto enabled
    if (module_exists('path')) {
      $this->addFieldMapping('path')
           ->issueGroup(t('DNM'));
      if (module_exists('pathauto')) {
        $this->addFieldMapping('pathauto')
             ->issueGroup(t('DNM'));
      }
    }

  } //construct

  // found at http://drupal.org/node/1516244#comment-6011854
  /*
  public function preImport() {
    dpm($this->termsQuery);

    parent::preImport();
    $vocabs = taxonomy_vocabulary_get_names();
    $vid = $vocabs[$this->destination->getBundle()]->vid;
    $query = $this->termsQuery; // $this->termsQuery is set to the $query that I submitted as my source sql
    if ($this->getItemLimit()>0) {
      $query->range(0, $this->getItemLimit());
    }
    $results = $query->execute()->fetchAllAssoc('tid'); //Returns the result set as an associative array keyed by the given field.
    foreach ($results as $tid=>$result) {
      if (!taxonomy_term_load($tid)) {
        $term = new StdClass();
        $term->tid = $tid;
        $term->name = 'Stub term: ' . $tid;
        $term->description = '';
        $term->vid = $vid;
        $status = drupal_write_record('taxonomy_term_data', $term);
      }
    }
  }
  */
  public function prepareRow($row){
    //dpm($row);
  }
}

class DownfallTermHierarchyMigration extends DownfallMigration {
  public function __construct() {
    parent::__construct();

    $this->description = t('Migrate term hierarchy from d6 to d7.');

    $this->dependencies = array('DownfallTermWow');

    $table_name = 'taxonomy_term_hierarchy'; //used a few times below

    $this->map = new MigrateSQLMap(
      $this->machineName,
      array(
        'tid' => array(
          'type' => 'int',
          'length' => 10,
          'not null' => FALSE,
          'description' => '',
        )
      ),
      //built in from migrate to map drupal terms automatically
      MigrateDestinationTable::getKeySchema($table_name)
    );

    //nuke hierarchy table

    $query = Database::getConnection('migrate', 'df6import')
           ->select('term_hierarchy', 'hierarchy')
           ->fields('hierarchy', array('tid', 'parent'));

    // Create a MigrateSource object, which manages retrieving the input data.
    $this->source = new MigrateSourceSQL($query, array(), NULL, array('map_joinable' => FALSE));

    // Set up our destination - terms in the migrate_example_beer_styles vocabulary
    $this->destination = new MigrateDestinationTable($table_name);

    // this ensures that vids from d6 line up with their new vids in new d7
    $this->addFieldMapping('tid', 'tid')
         ->sourceMigration('DownfallTermWoW');

    // important to note what's going on here. We're taking parent from source, mapping it to
    // parent in destination, but saying the DownfallTermWow migration will convert the ids
    $this->addFieldMapping('parent', 'parent')
         ->sourceMigration('DownfallTermWow')
         ->defaultValue(0);

  }
  // prepare should go here and truncate d7 table
   public function preImport() {
    $result = db_truncate('taxonomy_term_hierarchy')->execute();
  }

}