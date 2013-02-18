<?php

/**
 * Common mappings for the Drupal 6 node migrations.
 */
abstract class DownfallNodeMigration extends DrupalNode6Migration {
  public function __construct(array $arguments) {
    parent::__construct($arguments);

    // we don't really need this kind of mapping
    // $this->addFieldMapping('nid', 'nid')
    //      ->description('We have a common field to save the D6 nid');
  }

  /**
   * Call this from the prepare() method of a migration that contains media
   * image files, if you want to rewrite the IMG tags into media references.
   *
   * @param $entity
   *  Entity object being built.
   * @param $field
   *  Name of the text field within the entity to be modified. Defaults to 'body'.
   */
  static public function rewriteImgAssistTags($entity, $field = 'body') {
    if (is_array($entity->$field)) {
      migrate_instrument_start('MigrateDestinationMedia rewriteImgTags');
      foreach ($entity->$field as $language => $values) {
        $body = $values[0]['value'];
        break;
      }
      // Quickly skip any non-candidates
      if (!stristr($body, '[img_assist')) {
        migrate_instrument_stop('MigrateDestinationMedia rewriteImgTags');
        return;
      }
      // Pass full img tags into the callback
      $new_body = preg_replace_callback('|\[img_assist[^\]]*\]|i', "self::replaceCallback",
        $body);
      $entity->{$field}[$language][0]['value'] = $new_body;
      migrate_instrument_stop('MigrateDestinationMedia rewriteImgTags');
    }
  }

  /**
   * If a referenced image can be found in the files table, replace the <img> tag
   * with a media JSON reference.
   *
   * @param array $matches
   */
  static protected function replaceCallback(array $matches) {
    $src_matches = array();
    // Default to the original <img> tag
    $result = $matches[0];
    // the embed code
    $image_info = '';
    // Extract the src parameter
    if (preg_match('|\|nid=(\d+)\||i', $matches[0], $src_matches)) {

      // my work
      $src = $src_matches[1];
      $dest_image_nid = parent::handleSourceMigration('DownfallD2DNodeDfImage', $src);
      // end my work

      // Replace the scheme and host portions of the referenced URI with the
      // Drupal scheme as it's saved in the file_unmanaged table

      $fid = db_select('file_usage', 'f')
             ->fields('f', array('fid'))
             ->condition('id', basename($dest_image_nid))
             ->execute()
             ->fetchField();
      if ($fid) {
        $image_info = array(
          'type' => 'media',
          'view_mode' => 'media_preview',
          'fid' => $fid,
          'attributes' => array(
            'alt' => '',
            'title' => '',
            'class' => 'media-image',
            'typeof' => 'foaf:Image',
            'wysiwyg' => 1,
          ),
        );
        // Get the height and width parameters if present
        // preg_match('|width=[\'"]([^\'"]+)[\'"]|i', $matches[0], $width);
        // preg_match('|height=[\'"]([^\'"]+)[\'"]|i', $matches[0], $height);
        // image width
        // if ($width) {
        //   $image_info['attributes']['width'] = $width[1];
        // }
        // // image height
        // if ($height) {
        //   $image_info['attributes']['height'] = $height[1];
        // }

        $result = '[[' . drupal_json_encode($image_info) . ']]';
      }
    }
    return $result;
  }
}

/**
 * Dates - raid_event
 */

class DownfallDateNodeMigration extends DownfallNodeMigration {
  public function __construct(array $arguments) {

    parent::__construct($arguments);

    $this->addFieldMapping('field_event_date', 'field_startdate');
  }

  public function prepareRow($row){
    if (parent::prepareRow($row) === FALSE) {
      return FALSE;
    }


    $date_data = array(
      'from' => (string)$row->field_startdate[0],
      'to' => $row->{'field_startdate:value2'}[0],
    );

    // Here we're replacing the value of (d6) field_startdate with some json that indicates
    // beginning and end dates. We could have mapped a dummy field and then filled this in
    // with a lookup, but this is super clean.
    $row->field_startdate = drupal_json_encode($date_data);
  }

  /**
   * Implementation of Migration::prepare().
   */
  public function prepare($node, $row) {
    // This will replace any [img_assist] tags in the body with the media module's JSON reference
    parent::rewriteImgAssistTags($node);
  }
}

/**
 * Dates - old "event" type
 * Most of the magic here will be in the prepareRow stuff. This is the old "event" module.
 * It stored start/end times in it's own table. We're calling that below.
 */

class DownfallOldEventNodeMigration extends DownfallNodeMigration {
  public function __construct(array $arguments) {

    parent::__construct($arguments);

    $this->addFieldMapping('field_event_date', 'placeholder_date');
  }

  // public function query() {
  //   $query = parent::query();
  //   $query->range(0,10);
  //   return $query;
  // }

  public function prepareRow($row){
    if (parent::prepareRow($row) === FALSE) {
      return FALSE;
    }

    $d6_date_row = Database::getConnection('downfall_d6_pristine', $this->sourceConnection)
      ->select('event', e)
      ->fields('e', array('event_start', 'event_end'))
      ->condition('nid', $row->nid)
      ->execute()
      ->fetchObject();

    $date_data = array(
      'from' => (string)$d6_date_row->event_start,
      'to' => (string)$d6_date_row->event_end,
    );

    $row->placeholder_date = drupal_json_encode($date_data);
  }

  /**
   * Implementation of Migration::prepare().
   */
  public function prepare($node, $row) {
    // This will replace any [img_assist] tags in the body with the media module's JSON reference
    parent::rewriteImgAssistTags($node);
  }
}

/**
 * Blogs / generic nodes (story, page, blog)
 *
 * For any node that really only has this taxonomy field
 */

class DownfallGenericWowTermNodeMigration extends DownfallNodeMigration {
  public function __construct(array $arguments) {

    parent::__construct($arguments);

    // Note that we map migrated terms by the vocabulary ID.
    $this->addFieldMapping('field_wow_category', '5')
         ->sourceMigration('DownfallD2DTermWoW')
         ->arguments(array('source_type' => 'tid'));
  }

  /**
   * Implementation of Migration::prepare().
   */
  public function prepare($node, $row) {
    // This will replace any [img_assist] tags in the body with the media module's JSON reference
    parent::rewriteImgAssistTags($node);
  }
}

/**
 * Books
 */
class DownfallBookMigration extends DownfallNodeMigration {
  public function __construct(array $arguments) {
    parent::__construct($arguments);

    // Note that we map migrated terms by the vocabulary ID.
    $this->addFieldMapping('field_wow_category', '5')
         ->sourceMigration('DownfallD2DTermWoW')
         ->arguments(array('source_type' => 'tid'));
  }

  /**
   * Implementation of Migration::prepare().
   */
  public function prepare($node, $row) {
    // This will replace any [img_assist] tags in the body with the media module's JSON reference
    parent::rewriteImgAssistTags($node);
  }

  /**
     * Overrides parent::nodeQuery to add more data to the source, in our case,
     * book hierarchy stuff.
     */
    public function query() {

      // new, more inclusive
      $query = parent::query();
      // Add in book parent child relationships.
      $query->leftJoin('book', 'b', 'n.nid = b.nid');
      $query->addField('b', 'bid', 'book_id');
      $query->leftJoin('menu_links', 'ml', 'b.mlid = ml.mlid');
      $query->addField('ml', 'weight', 'book_weight');
      $query->addField('ml', 'mlid', 'mlid');
      $query->addField('ml', 'plid', 'plid');
      $query->orderBy('mlid');

      // dpq($query);
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
      $node->book['weight'] = $row->book_weight == '' ? 0 : $row->book_weight;
      // find new parent for *most* book pages
      $node->book['plid'] = $this->findNewPlid($row->plid);
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

      // 182 is the main handbook from the old sitem if source id is empty, set to 182, else lookup
      $dest_book_nid = $source_book_nid == '' ? '182' : parent::handleSourceMigration('DownfallD2DNodeBook', $source_book_nid);

      return $dest_book_nid;
    }

    /**
     * Returns the new parent mlid for a book node
     *
     * @param int $oldplid
     *   The parent id of the original d6 book node
     */
    protected function findNewPlid($oldplid){

      // we have the old plid, find corresponding nid
      $oldnid = Database::getConnection('downfall_d6_pristine', $this->sourceConnection)
        ->select('book', 'b')
        ->fields('b', array('nid'))
        ->condition('mlid', $oldplid)
        ->execute()
        ->fetchObject();

      if ($oldnid){
        // looukup new nid from old nid
        $newnid = parent::handleSourceMigration('DownfallD2DNodeBook', $oldnid->nid);
        // load the node to get at book data
        $parentnode = node_load($newnid);
        // if the node was created, it's part of a book menu hierarchy now
        $newplid = $parentnode->book['mlid'];
      } else{
        $newplid = 0;
      }
      return $newplid;
    }

}

/**
 * Forums
 */

class DownfallForumMigration extends DownfallNodeMigration {
  public function __construct(array $arguments) {

    parent::__construct($arguments);

    // Note that we map migrated terms by the vocabulary ID.
    $this->addFieldMapping('taxonomy_forums', '3')
         ->sourceMigration('DownfallD2DTermForums')
         ->arguments(array('source_type' => 'tid'));
  }

  /**
   * Implementation of Migration::prepare().
   */
  public function prepare($node, $row) {
    // This will replace any [img_assist] tags in the body with the media module's JSON reference
    parent::rewriteImgAssistTags($node);
  }
}

/**
 * Guild apps
 */

class DownfallGuildAppsMigration extends DownfallNodeMigration {

  // used for roles translation
  public $rolemap = array(
    0 => 'Healing',
    1 => 'Tanking',
    2 => 'DPS',
  );

  // used for raiding nights
  public $nightsmap = array(
    0 => 'Monday',
    1 => 'Tuesday',
    2 => 'Wednesday',
    3 => 'Thursday',
    4 => 'Friday',
    5 => 'Saturday',
    6 => 'Sunday',
  );

  public function __construct(array $arguments) {

    parent::__construct($arguments);

    // character info
    $this->addFieldMapping('field_app_char_name', 'field_toon_name');
    $this->addFieldMapping('field_app_race', 'field_race');
    $this->addFieldMapping('field_app_class', 'field_toon_class');
    $this->addFieldMapping('field_app_level', 'field_toon_level');
    $this->addFieldMapping('field_app_max_time', 'field_70_playtime');
    $this->addFieldMapping('field_app_current_server', 'field_server');
    $this->addFieldMapping('field_app_current_server_time', 'field_time_on_server');
    // raiding
    $this->addFieldMapping('field_app_talents', 'field_talent_build');
    $this->addFieldMapping('field_app_role_comfortable', 'field_role')
      ->callbacks(array($this, 'roleLookup'));
    $this->addFieldMapping('field_app_class_contributes', 'field_class_contribution');
    $this->addFieldMapping('field_app_instances_experience', 'field_raid_experience');
    $this->addFieldMapping('field_app_boss_favorite', 'field_favorite_encounter');
    $this->addFieldMapping('field_app_boss_least_favorite', 'field_least_favorite_encounter');
    $this->addFieldMapping('field_app_raid_nights', 'field_nights_available')
      ->callbacks(array($this, 'nightsLookup'));
    $this->addFieldMapping('field_app_pvp_interest', 'field_interested_pvp');
    // general questions
    $this->addFieldMapping('field_app_why_recruit', 'field_why');
    $this->addFieldMapping('field_app_why_apply', 'field_why_downfall');
    $this->addFieldMapping('field_app_get_out_of_membership', 'field_what_getting_out');
    $this->addFieldMapping('field_app_contribute_community', 'field_contribute');
    $this->addFieldMapping('field_app_references', 'field_references');
    $this->addFieldMapping('field_app_duration_of_stay', 'field_sticking_around');
    $this->addFieldMapping('field_app_cause_leave', 'field_leaving');
    $this->addFieldMapping('field_app_timezone', 'field_timezone');
    $this->addFieldMapping('field_app_anything_else', 'field_additional');
    // ui -> media field
    $this->addFieldMapping('field_app_ui_media', 'field_ui_ss_2')
      ->sourceMigration('DownfallD2DFiles');
    $this->addFieldMapping('field_app_ui_media:file_class')
             ->defaultValue('MigrateFileFid');
    $this->addFieldMapping('field_app_ui_media:preserve_files')
             ->defaultValue(TRUE);
    $this->addFieldMapping('field_app_ui_media:title', 'image_title_placeholder')
             ->defaultValue(t('Guild application UI screenshot'));
    $this->addFieldMapping('field_app_ui_media:language')
             ->defaultValue(LANGUAGE_NONE);
    // personal
    $this->addFieldMapping('field_app_how_long_wow', 'field_how_long_playing');
    $this->addFieldMapping('field_app_how_old', 'field_age');
    $this->addFieldMapping('field_app_yourself', 'field_about_you');
    $this->addFieldMapping('field_app_school_or_work', 'field_school_or_working');
    $this->addFieldMapping('field_app_hobbies', 'field_hobbies');
    $this->addFieldMapping('field_app_country_state', 'field_location');

    $this->addFieldMapping('field_app_open_closed', 'field_closed');

  }

  // roles need to be converted
  protected function roleLookup($value){
    return $this->rolemap[$value];
  }

  // nights need to be converted
  protected function nightsLookup($value){
    $nights = array();
    foreach ($value as $night){
      $nights[] = $this->nightsmap[$night];
    }
    return $nights;
  }

  // just here to limit results while testing
  // public function query() {
  //   $query = parent::query();
  //   $query->range(0,50);
  //   return $query;
  // }

  public function prepareRow($row){
    if (parent::prepareRow($row) === FALSE) {
      return FALSE;
    }

    // $d6_date_row = Database::getConnection('downfall_d6_pristine', $this->sourceConnection)
    //   ->select('event', e)
    //   ->fields('e', array('event_start', 'event_end'))
    //   ->condition('nid', $row->nid)
    //   ->execute()
    //   ->fetchObject();

  }
}

/**
 * Image to Media migration
 *
 * Notes: Look at beer.inc for a regular DynamicMigration. See app_ui image mapped above
 * Then check migrate_extras_media.migrate.inc: field_media_image mapping.
 */

class DownfallImageMigration extends DownfallNodeMigration {


  public function __construct(array $arguments) {

    parent::__construct($arguments);

    //testing with static fid
    $this->addFieldMapping('field_df_image', 'image_lookup_placeholder')
      ->sourceMigration('DownfallD2DFiles');
    $this->addFieldMapping('field_df_image:file_class')
      ->defaultValue('MigrateFileFid');
    $this->addFieldMapping('field_df_image:preserve_files')
      ->defaultValue(TRUE);
    $this->addFieldMapping('field_df_image:title', 'image_title_placeholder')
      ->defaultValue(t('Downfall image'));
    $this->addFieldMapping('field_app_ui:language')
      ->defaultValue(LANGUAGE_NONE);

   // Note that we map migrated terms by the vocabulary ID.
   $this->addFieldMapping('field_gallery', '8')
      ->sourceMigration('DownfallD2DTermGallery')
      ->arguments(array('source_type' => 'tid'));
  }

  // just here to limit results while testing
  // public function query() {
  //   $query = parent::query();
  //   $query->range(0,50);
  //   return $query;
  // }

  public function prepareRow($row){
    if (parent::prepareRow($row) === FALSE) {
      return FALSE;
    }

    // do a lookup on the d6 image table for the _original file
    $d6_file = Database::getConnection('downfall_d6_pristine', $this->sourceConnection)
      ->select('image', i)
      ->fields('i', array('fid'))
      ->condition('nid', $row->nid)
      ->condition('image_size', '_original')
      ->execute()
      ->fetchObject();

    $row->image_lookup_placeholder = $d6_file->fid;

  }
}

/**
 * A new files migration that handles media filetypes better
 */
class DownfallFile6Migraton extends DrupalFile6Migration{
  public function __construct(array $arguments) {
    parent::__construct($arguments);

    $this->addFieldMapping('type', 'filemime')
      ->callbacks(array($this, 'fileTypes'));
  }

  // public function query() {
  //   $query = parent::query();
  //   $query->range(0,10);
  //   return $query;
  // }

  // quick file types based on Media's defaults of image, video, audio, document
  protected function fileTypes($mime){
    $mimestring = explode("/", $mime);
    switch($mimestring[0]){
      case 'application':
      case 'text':
        $type = 'document';
        break;
      case 'video':
        $type = 'video';
        break;
      case 'audio':
        $type = 'audio';
        break;
      default:
        $type = 'image';
    }
    return $type;
  }
}

/**
 * A new picture migration that handles the whole media-filetypes issue better
 */
class DownfallPicture6Migration extends DrupalPicture6Migration{
  public function __construct(array $arguments) {
    parent::__construct($arguments);

    // $this->addFieldMapping(NULL, 'filemime');
    $this->addFieldMapping('type', 'type')
      ->defaultValue('image');
  }
}


/**
 * Common mappings for the Drupal 6 comments
 */
class DownfallCommentMigration extends DrupalComment6Migration {
  public function __construct(array $arguments) {
    parent::__construct($arguments);

  }

  // public function query() {
  //   $query = parent::query();
  //   $query->range(0,25);
  //   return $query;
  // }

  /**
   * Implementation of Migration::prepare().
   */
  public function prepare($comment, $row) {
    // dpm($comment);
    // dpm($row);
    // This will replace any [img_assist] tags in the body with the media module's JSON reference
    $this->rewriteImgAssistTags($comment);
  }

  /**
   * Call this from the prepare() method of a migration that contains media
   * image files, if you want to rewrite the IMG tags into media references.
   *
   * @param $entity
   *  Entity object being built.
   * @param $field
   *  Name of the text field within the entity to be modified. Defaults to 'body'.
   */
  static public function rewriteImgAssistTags($entity, $field = 'comment_body') {
    if (is_array($entity->$field)) {
      migrate_instrument_start('MigrateDestinationMedia rewriteImgTags');
      foreach ($entity->$field as $language => $values) {
        $body = $values[0]['value'];
        break;
      }
      // Quickly skip any non-candidates
      if (!stristr($body, '[img_assist')) {
        migrate_instrument_stop('MigrateDestinationMedia rewriteImgTags');
        return;
      }
      // Pass full img tags into the callback
      $new_body = preg_replace_callback('|\[img_assist[^\]]*\]|i', "self::replaceCallback",
        $body);
      $entity->{$field}[$language][0]['value'] = $new_body;
      migrate_instrument_stop('MigrateDestinationMedia rewriteImgTags');
    }
  }

  /**
   * If a referenced image can be found in the files table, replace the <img> tag
   * with a media JSON reference.
   *
   * @param array $matches
   */
  static protected function replaceCallback(array $matches) {

    $src_matches = array();
    // Default to the original <img> tag
    $result = $matches[0];
    // the embed code
    $image_info = '';
    // Extract the src parameter
    if (preg_match('|\|nid=(\d+)\||i', $matches[0], $src_matches)) {

      // my work
      $src = $src_matches[1];
      $dest_image_nid = parent::handleSourceMigration('DownfallD2DNodeDfImage', $src);
      // end my work

      // Replace the scheme and host portions of the referenced URI with the
      // Drupal scheme as it's saved in the file_unmanaged table

      $fid = db_select('file_usage', 'f')
             ->fields('f', array('fid'))
             ->condition('id', basename($dest_image_nid))
             ->execute()
             ->fetchField();
      if ($fid) {
        $image_info = array(
          'type' => 'media',
          'view_mode' => 'media_preview',
          'fid' => $fid,
          'attributes' => array(
            'alt' => '',
            'title' => '',
            'class' => 'media-image',
            'typeof' => 'foaf:Image',
            'wysiwyg' => 1,
          ),
        );
        // Get the height and width parameters if present
        // preg_match('|width=[\'"]([^\'"]+)[\'"]|i', $matches[0], $width);
        // preg_match('|height=[\'"]([^\'"]+)[\'"]|i', $matches[0], $height);
        // image width
        // if ($width) {
        //   $image_info['attributes']['width'] = $width[1];
        // }
        // // image height
        // if ($height) {
        //   $image_info['attributes']['height'] = $height[1];
        // }

        $result = '[[' . drupal_json_encode($image_info) . ']]';
      }
    }
    return $result;
  }

}

/**
 * Guild apps
 */

class DownfallRaidMigration extends DownfallNodeMigration {

  public function __construct(array $arguments) {

    parent::__construct($arguments);

    // ui -> media field
    $this->addFieldMapping('field_raid_mascot_image', 'field_mascot')
      ->sourceMigration('DownfallD2DFiles');
    $this->addFieldMapping('field_raid_mascot_image:file_class')
             ->defaultValue('MigrateFileFid');
    $this->addFieldMapping('field_raid_mascot_image:preserve_files')
             ->defaultValue(TRUE);
    $this->addFieldMapping('field_raid_mascot_image:title', 'image_title_placeholder')
             ->defaultValue(t('Raid mascot screenshot'));
    $this->addFieldMapping('field_raid_mascot_image:language')
             ->defaultValue(LANGUAGE_NONE);
  }

  // just here to limit results while testing
  // public function query() {
  //   $query = parent::query();
  //   $query->range(0,50);
  //   return $query;
  // }

  public function prepareRow($row){
    if (parent::prepareRow($row) === FALSE) {
      return FALSE;
    }

    // $d6_date_row = Database::getConnection('downfall_d6_pristine', $this->sourceConnection)
    //   ->select('event', e)
    //   ->fields('e', array('event_start', 'event_end'))
    //   ->condition('nid', $row->nid)
    //   ->execute()
    //   ->fetchObject();

  }
}