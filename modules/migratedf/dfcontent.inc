<?php

/**
 * @file
 * A basic example of using the Migrate module to import taxonomy, users, nodes,
 * and comments.
 *
 * The basic idea is
 * - The users in the source application are listed in the
 *   migrate_example_beer_account table and are transformed into Drupal users.
 * - Drupal "beer" nodes describe beers; The information to create the nodes
 *   comes from the migrate_example_beer_node table.
 * - Taxonomy terms for the beer nodes (ale, pilsner) come from the
 *   migrate_example_beer_topic table and they are applied to nodes using the
 *   source information in the migrate_example_beer_topic_node table.
 * - Comments to be attached to the beer nodes are described in the source
 *   migrate_example_beer_comment table.
 *
 * We will use the Migrate API to import and transform this data and turn it into
 * a working Drupal system.
 */

/**
 * To define a migration process from a set of source data to a particular
 * kind of Drupal object (for example, a specific node type), you define
 * a class derived from Migration. You must define a constructor to initialize
 * your migration object. By default, your class name will be the "machine name"
 * of the migration, by which you refer to it. Note that the machine name is
 * case-sensitive.
 *
 * In any serious migration project, you will find there are some options
 * which are common to the individual migrations you're implementing. You can
 * define an abstract intermediate class derived from Migration, then derive your
 * individual migrations from that, to share settings, utility functions, etc.
 */

/**
 * BasicExampleMigration = DownfallMigration
 */

abstract class DownfallMigration extends Migration {
  public function __construct() {
    // Always call the parent constructor first for basic setup
    parent::__construct(MigrateGroup::getInstance('downfall', array('default')));

    // With migrate_ui enabled, migration pages will indicate people involved in
    // the particular migration, with their role and contact info. We default the
    // list in the shared class; it can be overridden for specific migrations.
    $this->team = array(
      new MigrateTeamMember('Chris Bloom', 'bloomcb@gmail.com', t('Guild Site Runner')),
    );

    // Individual mappings in a migration can be linked to a ticket or issue
    // in an external tracking system. Define the URL pattern here in the shared
    // class with ':id:' representing the position of the issue number, then add
    // ->issueNumber(1234) to a mapping.
    $this->issuePattern = 'http://drupal.org/node/:id:';
  }
}

class DownfallVocabularyMigration extends DownfallMigration {
  public function __construct() {
    parent::__construct();
    // Human-friendly description of your migration process. Be as detailed as you
    // like.
    $this->description = t('Migrate taxonomies from d6 to d7.');
    $table_name = 'taxonomy_vocabulary';
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

    // Set up our destination - terms in the migrate_example_beer_styles vocabulary
    $this->destination = new MigrateDestinationTable($table_name);

    $this->addSimpleMappings(array('name', 'description', 'module', 'weight'));
    $this->addFieldMapping('hierarchy')
         ->defaultValue(0);
    //maps to destination with modification to source, see function below
    $this->addFieldMapping('machine_name', 'name')
         ->callbacks(array($this, 'vocabMachineName'));
    $this->addFieldMapping(NULL, 'vid')
         ->issueGroup(t('DNM'));
    $this->addUnmigratedDestinations(array('vid'));
  }

  public function vocabMachineName($args){
    dpm($args);
    //$machine_readable = strtolower($args);
    return preg_replace('@[^a-z0-9_]+@','_',strtolower($args));
  }

}

/**
 * There are four essential components to set up in your constructor:
 *  $this->source - An instance of a class derived from MigrateSource, this
 *    will feed data to the migration.
 *  $this->destination - An instance of a class derived from MigrateDestination,
 *    this will receive data that originated from the source and has been mapped
 *    by the Migration class, and create Drupal objects.
 *  $this->map - An instance of a class derived from MigrateMap, this will keep
 *    track of which source items have been imported and what destination objects
 *    they map to.
 *  Mappings - Use $this->addFieldMapping to tell the Migration class what source
 *    fields correspond to what destination fields, and additional information
 *    associated with the mappings.
 */
class DownfallTermWowMigration extends DownfallMigration {
  public function __construct() {
    parent::__construct();
    // Human-friendly description of your migration process. Be as detailed as you
    // like.
    $this->description = t('Migrate terms from d6 to d7.');
    $this->softDependencies = array('DownfallVocabulary');

    // Create a map object for tracking the relationships between source rows
    // and their resulting Drupal objects. Usually, you'll use the MigrateSQLMap
    // class, which uses database tables for tracking. Pass the machine name
    // (BeerTerm) of this migration to use in generating map and message tables.
    // And, pass schema definitions for the primary keys of the source and
    // destination - we need to be explicit for our source, but the destination
    // class (MigrateDestinationTerm) knows its schema already.
    // $this->map = new MigrateSQLMap($this->machineName,
    //     array(
    //       'style' => array('type' => 'varchar',
    //                        'length' => 255,
    //                        'not null' => TRUE,
    //                        'description' => 'Topic ID',
    //                       )
    //     ),
    //     //built in from migrate to map drupal terms automatically
    //     MigrateDestinationTerm::getKeySchema()
    //   );

      //dpm($this->machineName);
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

    // In this example, we're using tables that have been added to the existing
    // Drupal database but which are not Drupal tables. You can examine the
    // various tables (starting here with migrate_example_beer_topic) using a
    // database browser like phpMyAdmin.
    // First, we set up a query for this data. Note that by ordering on
    // style_parent, we guarantee root terms are migrated first, so the
    // parent_name mapping below will find that the parent exists.
    // $query = db_select('migrate_example_beer_topic', 'met')
    //          ->fields('met', array('style', 'details', 'style_parent', 'region', 'hoppiness'))
    //          // This sort assures that parents are saved before children.
    //          ->orderBy('style_parent', 'ASC');

    $query = Database::getConnection('migrate', 'df6import')
           ->select('term_data', 'td')
           ->fields('td', array('tid', 'vid', 'name', 'description', 'weight'));
    //$query->condition('vid', 5, '=');
    $query->join('term_hierarchy', 'th', 'th.tid = td.tid');
    $query->addField('th', 'parent'); // need to get actual parent name, use sourceMigration to get mappings properly
    $query->orderBy('th.parent');

    // Create a MigrateSource object, which manages retrieving the input data.
    $this->source = new MigrateSourceSQL($query, array(), NULL, array('map_joinable' => FALSE));

    // Set up our destination - terms in the migrate_example_beer_styles vocabulary
    $this->destination = new MigrateDestinationTerm('wow');

    // Assign mappings TO destination fields FROM source fields. To discover
    // the names used in these calls, use the drush commands
    // drush migrate-fields-destination BeerTerm
    // drush migrate-fields-source BeerTerm
    //$this->addFieldMapping('tid', 'tid');
    //$this->addFieldMapping('vid', 'vid');
    $this->addFieldMapping('name', 'name');
    $this->addFieldMapping('description', 'description');
    $this->addFieldMapping('weight', 'weight');
    $this->addFieldMapping('parent', 'parent');

    // Documenting your mappings makes it easier for the whole team to see
    // exactly what the status is when developing a migration process.
    // $this->addFieldMapping('parent_name', 'style_parent')
    //      ->description(t('The incoming style_parent field is the name of the term parent'));

    // Mappings are assigned issue groups, by which they are grouped on the
    // migration info page when the migrate_ui module is enabled. The default
    // is 'Done', indicating active mappings which need no attention. A
    // suggested practice is to use groups of:
    // Do Not Migrate (or DNM) to indicate source fields which are not being used,
    //  or destination fields not to be populated by migration.
    // Client Issues to indicate input from the client is needed to determine
    //  how a given field is to be migrated.
    // Implementor Issues to indicate that the client has provided all the
    //  necessary information, and now the implementor needs to complete the work.
    // $this->addFieldMapping(NULL, 'hoppiness')
    //      ->description(t('This info will not be maintained in Drupal'))
    //      ->issueGroup(t('DNM'));

    // Open mapping issues can be assigned priorities (the default is
    // MigrateFieldMapping::ISSUE_PRIORITY_OK). If you're using an issue
    // tracking system, and have defined issuePattern (see BasicExampleMigration
    // above), you can specify a ticket/issue number in the system on the
    // mapping and migrate_ui will link directory to it.
    // $this->addFieldMapping(NULL, 'region')
    //      ->description('Will a field be added to the vocabulary for this?')
    //      ->issueGroup(t('Client Issues'))
    //      ->issuePriority(MigrateFieldMapping::ISSUE_PRIORITY_MEDIUM)
    //      ->issueNumber(770064);

    // It is good practice to account for all source and destination fields
    // explicitly - this makes sure that everyone understands exactly what is
    // being migrated and what is not. Also, migrate_ui highlights unmapped
    // fields, or mappings involving fields not in the source and destination,
    // so if (for example) a new field is added to the destination field it's
    // immediately visible, and you can find out if anything needs to be
    // migrated into it.
    // $this->addFieldMapping('format')
    //      ->issueGroup(t('DNM'));
    // $this->addFieldMapping('weight')
    //      ->issueGroup(t('DNM'));
    // $this->addFieldMapping('parent')
    //      ->issueGroup(t('DNM'));

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
  } //construc

  public function prepareRow($row){
    //dpm($row);
  }
}