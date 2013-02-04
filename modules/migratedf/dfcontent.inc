<?php

/**
 * Common mappings for the Drupal 6 node migrations.
 * This is just a demo, we're not actually using
 */
abstract class DownfallNodeMigration extends DrupalNode6Migration {
  public function __construct(array $arguments) {
    parent::__construct($arguments);

    $this->addFieldMapping('nid', 'nid')
         ->description('We have a common field to save the D6 nid');
  }
}

/**
 * Dates
 */

class DownfallDateNodeMigration extends DrupalNode6Migration {
  public function __construct(array $arguments) {

    parent::__construct($arguments);

    $this->addFieldMapping('field_event_date', 'field_startdate');
  }

  public function prepareRow($row){
    if (parent::prepareRow($row) === FALSE) {
      return FALSE;
    }

    // leaving this around because it's a good dbcommenction example
    // $d6_date_row = Database::getConnection('downfall_d6_pristine', $this->sourceConnection)
    //   ->select('content_field_startdate', i)
    //   ->fields('i', array('field_startdate_value2'))
    //   ->condition('vid', $row->vid)
    //   ->execute()
    //   ->fetchObject();

    $date_data = array(
      'from' => (string)$row->field_startdate[0],
      'to' => $row->{'field_startdate:value2'}[0],
    );

    // Here we're replacing the value of (d6) field_startdate with some json that indicates
    // beginning and end dates. We could have mapped a dummy field and then filled this in
    // with a lookup, but this is super clean.
    $row->field_startdate = drupal_json_encode($date_data);
  }


}

/**
 * Blogs
 */

class DownfallGenericWowTermNodeMigration extends DrupalNode6Migration {
  public function __construct(array $arguments) {

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
    parent::__construct($arguments);
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

/**
 * Forums
 */

class DownfallForumMigration extends DrupalNode6Migration {
  public function __construct(array $arguments) {

    parent::__construct($arguments);

    // Note that we map migrated terms by the vocabulary ID.
    $this->addFieldMapping('taxonomy_forums', '3')
         ->sourceMigration('DownfallD2DTermForums')
         ->arguments(array('source_type' => 'tid'));
  }
}