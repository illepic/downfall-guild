<?php

/**
 * Common mappings for the Drupal 6 node migrations.
 */
abstract class DownfallNodeMigration extends DrupalNode6Migration {
  public function __construct(array $arguments) {
    parent::__construct($arguments);

    $this->addFieldMapping('nid', 'nid')
         ->description('We have a common field to save the D6 nid');
  }
}

/**
 * Blogs
 */

class DownfallBlogMigration extends DrupalNode6Migration {
  public function __construct(array $arguments) {
    // $this->sourceFields['lead_graphic'] = 'Lead graphic string from D6';
    // $this->sourceFields['summary'] = 'Summary string from D6';

    parent::__construct($arguments);

    // Note that we map migrated terms by the vocabulary ID.
    $this->addFieldMapping('field_wow_category', '5')
         ->sourceMigration('DownfallD2DTermWoW')
         ->arguments(array('source_type' => 'tid'));
  }
}

/**
 * Books
 */
class DownfallBookMigration extends DrupalNode6Migration {
  public function __construct(array $arguments) {
    // Add any other data we're pulling into the source row, before the parent
    // constructor.
    // $this->sourceFields['lead_graphic'] = 'Lead graphic string from D6';
    // $this->sourceFields['summary'] = 'Summary string from D6';

    parent::__construct($arguments);

    // $this->addFieldMapping('field_image', 'field_lead_graphic')
    //      ->sourceMigration('Image');
    // // Note that we map migrated terms by the vocabulary ID.
    // $this->addFieldMapping('field_countries', '1')
    //      ->sourceMigration('Countries')
    //      ->arguments(array('source_type' => 'tid'));
    // $this->addFieldMapping('field_topics', '2')
    //      ->sourceMigration('Topics')
    //      ->arguments(array('source_type' => 'tid'));
  }

  /**
     * Overrides parent::nodeQuery to add more data to the source, in our case,
     * book hierarchy stuff.
     */
    public function query() {
      // dpm('did this query get called?');

      $query = parent::query();
      // Add in book parent child relationships.
      $query->join('book', 'b', 'n.nid = b.nid');
      $query->addField('b', 'bid', 'book_id');
      $query->join('menu_links', 'ml', 'b.mlid = ml.mlid');
      $query->addField('ml', 'weight', 'book_weight');

      return $query;
    }

     /**
     * Acts right after a book node has been saved. Map the book hierarchy.
     *
     * @param object $node
     *   A node object for the newly migrated book.
     * @param stdClass $row
     *   An object representing data from the source row.
     */
     public function complete($node, stdClass $row) {
      // If this is a top-level book, don't set a parent.
      $book_id = $row->nid == $row->book_id ? $node->nid : $this->lookupMigratedBook($row->book_id);
      // Book id - effectively, parent nid.
      $node->book['bid'] = $book_id;
      $node->book['nid'] = $node->nid;
      $node->book['weight'] = $row->book_weight;
      _book_update_outline($node);
      node_save($node);
    }

    /**
     * Returns a mapping for a migrated book.
     *
     * @param int $source_book_nid
     *   Nid of book in source database to lookup.
     */
    protected function lookupMigratedBook($source_book_nid) {
      // dpm('in lookupMigratedBook');
      $dest_book_nid = parent::handleSourceMigration('DownfallD2DNodeBook', $source_book_nid);
      return $dest_book_nid;
    }
}

// /**
//  * DownfallMigration - PURELY MIGRATE MODULE
//  */

// abstract class DownfallMigration extends Migration {
//   public function __construct() {
//     // Always call the parent constructor first for basic setup
//     parent::__construct(MigrateGroup::getInstance('downfall', array('default')));

//     $this->team = array(
//       new MigrateTeamMember('Chris Bloom', 'bloomcb@gmail.com', t('Guild Site Runner')),
//     );
//   }

//   // make lowercase, space removed machine names
//   public function vocabMachineName($args){
//     return preg_replace('@[^a-z0-9_]+@','_',strtolower($args));
//   }
// }

// /*
//  * Vocabs
//  */
// class DownfallVocabularyMigration extends DownfallMigration {
//   public function __construct() {
//     parent::__construct();

//     $this->description = t('Migrate taxonomies from d6 to d7.');

//     $table_name = 'taxonomy_vocabulary'; //gets used a few times

//     $this->map = new MigrateSQLMap(
//       $this->machineName,
//       array(
//         'vid' => array(
//           'type' => 'int',
//           'length' => 10,
//           'not null' => FALSE,
//           'description' => '',
//         )
//       ),
//       //built in from migrate to map drupal terms automatically
//       MigrateDestinationTable::getKeySchema($table_name)
//     );

//     $query = Database::getConnection('migrate', 'df6import')
//            ->select('vocabulary', 'vocab')
//            ->fields('vocab', array('vid', 'name', 'description', 'module', 'weight'));

//     // Create a MigrateSource object, which manages retrieving the input data.
//     $this->source = new MigrateSourceSQL($query, array(), NULL, array('map_joinable' => FALSE));

//     // Set up our destination using a generic table since there is none prebuilt for full vocabs
//     $this->destination = new MigrateDestinationTable($table_name);

//     $this->addSimpleMappings(array('name', 'description', 'module', 'weight'));
//     $this->addFieldMapping('hierarchy')
//          ->defaultValue(0);
//     //maps to destination with modification to source, see function below
//     $this->addFieldMapping('machine_name', 'name')
//          ->callbacks(array($this, 'vocabMachineName')); // part of parent class
//     //map unused source, usually do this for primary keys
//     $this->addFieldMapping(NULL, 'vid')
//          ->issueGroup(t('DNM'));
//     $this->addUnmigratedDestinations(array('vid'));
//   }

// }

// /**
//  * Terms
//  */
// class DownfallTermWowMigration extends DownfallMigration {
//   public function __construct() {
//     parent::__construct();

//     $this->description = t('Migrate terms from d6 to d7.');

//     $this->dependencies = array('DownfallVocabulary');

//     $this->map = new MigrateSQLMap($this->machineName,
//       array(
//         'tid' => array('type' => 'int',
//                          'length' => 10,
//                          'not null' => FALSE,
//                          'description' => '',
//                         )
//       ),
//       //built in from migrate to map drupal terms automatically
//       MigrateDestinationTerm::getKeySchema()
//     );


//     $query = Database::getConnection('migrate', 'df6import')
//            ->select('term_data', 'td')
//            ->fields('td', array('tid', 'vid', 'name', 'description', 'weight'));
//     $query->join('term_hierarchy', 'th', 'th.tid = td.tid');
//     $query->addField('th', 'parent');
//     //$query->groupBy('td.vid');
//     $query->orderBy('td.vid, th.parent');

//     //saving to get at this later
//     $this->termsQuery = $query;

//     // Create a MigrateSource object, which manages retrieving the input data.
//     $this->source = new MigrateSourceSQL($query, array(), NULL, array('map_joinable' => FALSE));

//     // Set up our destination - terms in the migrate_example_beer_styles vocabulary
//     $this->destination = new MigrateDestinationTerm('wow'); // this doesn't really matter below

//     // Assign mappings TO destination fields FROM source fields. To discover
//     // the names used in these calls, use the drush commands
//     // drush migrate-fields-destination BeerTerm
//     // drush migrate-fields-source BeerTerm

//     // this ensures that vids from d6 line up with their new vids in new d7
//     $this->addFieldMapping('vid', 'vid')
//          ->sourceMigration('DownfallVocabulary');

//     // 'parent' is something built into Migrate
//     $this->addFieldMapping('parent', 'parent')
//          ->sourceMigration($this->machineName);

//     $this->addSimpleMappings(array('name', 'description', 'weight'));

//     // We conditionally DNM these fields, so your field mappings will be clean
//     // whether or not you have path and or pathauto enabled
//     if (module_exists('path')) {
//       $this->addFieldMapping('path')
//            ->issueGroup(t('DNM'));
//       if (module_exists('pathauto')) {
//         $this->addFieldMapping('pathauto')
//              ->issueGroup(t('DNM'));
//       }
//     }

//   } //construct

//   // found at http://drupal.org/node/1516244#comment-6011854
//   /*
//   public function preImport() {
//     dpm($this->termsQuery);

//     parent::preImport();
//     $vocabs = taxonomy_vocabulary_get_names();
//     $vid = $vocabs[$this->destination->getBundle()]->vid;
//     $query = $this->termsQuery; // $this->termsQuery is set to the $query that I submitted as my source sql
//     if ($this->getItemLimit()>0) {
//       $query->range(0, $this->getItemLimit());
//     }
//     $results = $query->execute()->fetchAllAssoc('tid'); //Returns the result set as an associative array keyed by the given field.
//     foreach ($results as $tid=>$result) {
//       if (!taxonomy_term_load($tid)) {
//         $term = new StdClass();
//         $term->tid = $tid;
//         $term->name = 'Stub term: ' . $tid;
//         $term->description = '';
//         $term->vid = $vid;
//         $status = drupal_write_record('taxonomy_term_data', $term);
//       }
//     }
//   }
//   */
//   public function prepareRow($row){
//     //dpm($row);
//   }
// }

// // Term hierarchies
// class DownfallTermHierarchyMigration extends DownfallMigration {
//   public function __construct() {
//     parent::__construct();

//     $this->description = t('Migrate term hierarchy from d6 to d7.');

//     $this->dependencies = array('DownfallTermWow');

//     $table_name = 'taxonomy_term_hierarchy'; //used a few times below

//     $this->map = new MigrateSQLMap(
//       $this->machineName,
//       array(
//         'tid' => array(
//           'type' => 'int',
//           'length' => 10,
//           'not null' => FALSE,
//           'description' => '',
//         )
//       ),
//       //built in from migrate to map drupal terms automatically
//       MigrateDestinationTable::getKeySchema($table_name)
//     );

//     //nuke hierarchy table

//     $query = Database::getConnection('migrate', 'df6import')
//            ->select('term_hierarchy', 'hierarchy')
//            ->fields('hierarchy', array('tid', 'parent'));

//     // Create a MigrateSource object, which manages retrieving the input data.
//     $this->source = new MigrateSourceSQL($query, array(), NULL, array('map_joinable' => FALSE));

//     // Set up our destination - terms in the migrate_example_beer_styles vocabulary
//     $this->destination = new MigrateDestinationTable($table_name);

//     // this ensures that vids from d6 line up with their new vids in new d7
//     $this->addFieldMapping('tid', 'tid')
//          ->sourceMigration('DownfallTermWoW');

//     // important to note what's going on here. We're taking parent from source, mapping it to
//     // parent in destination, but saying the DownfallTermWow migration will convert the ids
//     $this->addFieldMapping('parent', 'parent')
//          ->sourceMigration('DownfallTermWow')
//          ->defaultValue(0);

//   }
//   // prepare should go here and truncate d7 table
//    public function preImport() {
//     $result = db_truncate('taxonomy_term_hierarchy')->execute();
//   }

// }

// // user role migration
// class DownfallRoleMigration extends DownfallMigration {

//   /* change all this */
//   public function __construct() {
//     parent::__construct();

//     $this->description = t('user role migration');

//     $query = Database::getConnection('migrate', 'df6import')
//            ->select('role', 'role')
//            ->fields('role', array('rid', 'name'));

//     // Create a MigrateSource object, which manages retrieving the input data.
//     $this->source = new MigrateSourceSQL($query, array(), NULL, array('map_joinable' => FALSE));

//     $this->destination = new MigrateDestinationRole();

//     $this->map = new MigrateSQLMap( $this->machineName,
//       array(
//         'rid' => array(
//           'type' => 'int',
//           'unsigned' => TRUE,
//           'not null' => TRUE,
//         )
//       ),
//       MigrateDestinationRole::getKeySchema()
//     );

//     // $this->addSimpleMappings(array('rid', 'name'));
//     // $this->addFieldMapping('rid', 'rid');
//     $this->addFieldMapping('name', 'name');
//     $this->addFieldMapping('weight')->defaultValue(0);
//     // $this->addFieldMapping('is_new')
//     //   ->defaultValue(TRUE);
//   }

//   public function preImport() {
//      parent::preImport();
//      // really just want the original rids
//      //ALTER TABLE theTableInQuestion AUTO_INCREMENT=1234
//      $result = db_query('ALTER TABLE role AUTO_INCREMENT=1');
//    }
// }

// // user migrate
// // notes 10/13: fill out mappings
// class DownfallusersMigration extends DownfallMigration {
//   public function __construct(){
//     parent::__construct();
//     $this->description = t('User migrate');
//     $this->dependencies = array('DownfallRole');

//     // some field definitions; roles will be added later in prepareRow()
//     $source_fields = array(
//       'uid' => t('User ID'),
//       'roles' => t('The set of roles assigned to a user.'),
//     );

//     // only import active users from the old db
//     $query = Database::getConnection('migrate', 'df6import')
//       ->select('users', 'u')
//       ->fields('u', array('uid', 'name', 'pass', 'mail', 'created', 'access', 'login', 'status', 'init'))
//       // ->condition('u.status', 1, '=')
//       ->condition('u.uid', 1, '>')
//       ->orderBy('u.uid', 'ASC');
//     $this->source = new MigrateSourceSQL($query, $source_fields, NULL, array('map_joinable' => FALSE));
//     $this->destination = new MigrateDestinationUser(array('md5_passwords' => TRUE));
//     $this->map = new MigrateSQLMap($this->machineName,
//       array(
//         'uid' => array(
//           'type' => 'int',
//           'unsigned' => TRUE,
//           'not null' => TRUE,
//           'description' => 'D6 Unique User ID',
//           'alias' => 'u',
//         )
//       ),
//       MigrateDestinationUser::getKeySchema()
//     );

//     $this->addFieldMapping('is_new')->defaultValue(TRUE);
//     $this->addFieldMapping('uid', 'uid');
//     $this->addFieldMapping('name', 'name')->dedupe('users', 'name');
//     $this->addFieldMapping('pass', 'pass');
//     $this->addFieldMapping('mail', 'mail')->dedupe('users', 'mail');
//     $this->addFieldMapping('language')->defaultValue('');
//     $this->addFieldMapping('theme')->defaultValue('');
//     $this->addFieldMapping('signature')->defaultValue('');
//     $this->addFieldMapping('signature_format')->defaultValue('filtered_html');
//     $this->addFieldMapping('created', 'created');
//     $this->addFieldMapping('access', 'access');
//     $this->addFieldMapping('login', 'login');
//     $this->addFieldMapping('status', 'status');
//     $this->addFieldMapping('picture')->defaultValue(0);
//     $this->addFieldMapping('init', 'init');
//     $this->addFieldMapping('timezone')->defaultValue(NULL);
//     $this->addFieldMapping('path')->issueGroup(t('DNM')); // DNM = Do Not Map
//     $this->addFieldMapping('pathauto_perform_alias')->defaultValue('1');
//     $this->addFieldMapping('roles', 'roles'); //this neesd to be an array of roles, build below
//   }

//   // FIX THIS
//   public function prepareRow($current_row) {
//     $source_id = $current_row->uid;
//     // $query = db_select(REDCAT_MIGRATION_DATABASE_NAME .'.users_roles', 'r')
//     //   ->fields('r', array('uid', 'rid'))
//     //   ->condition('r.uid', $source_id, '=');
//     $query = Database::getConnection('migrate', 'df6import')
//       ->select('users_roles', 'r')
//       ->fields('r', array('uid', 'rid'))
//       ->condition('r.uid', $source_id, '=');
//     $results = $query->execute();
//     $roles = array('2' => '2');
//     foreach ($results as $row) {
//       $roles[$row->rid] = $row->rid;
//     }
//     $current_row->roles = $roles;
//     return TRUE;
//     // return FALSE;
//     // return FALSE if you wish to skip a particular row
//   }

// }