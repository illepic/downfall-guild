<?php
/**
 * @file
 * Implementation of DrupalNodeMigration for Drupal 7 sources.
 */

/**
 * Handling specific to a Drupal 7 source for nodes.
 */
class DrupalNode7Migration extends DrupalNodeMigration {
  /**
   * @param array $arguments
   */
  public function __construct(array $arguments) {
    parent::__construct($arguments);

    // Remove fields no longer relevent in D7 (now part of the body field).
    unset($this->sourceFields['format']);
    unset($this->sourceFields['teaser']);

    $this->source = new MigrateSourceSQL($this->query(), $this->sourceFields, NULL,
      $this->sourceOptions);

    $this->addFieldMapping('language', 'language')
         ->defaultValue($this->defaultLanguage);

    if (field_info_instance('node', 'body', $this->destinationType)) {
      $this->addFieldMapping('body:summary', 'body:summary');
      $this->addFieldMapping('body:format', 'body:format')
           ->callbacks(array($this, 'mapFormat'));
    }
    else {
      $this->addUnmigratedSources(array('body:summary', 'body:format'));
    }

    /** @todo Prevent stub creation when tnid == 0
    $this->addFieldMapping('tnid', 'tnid', FALSE)
         ->sourceMigration($arguments['machine_name']);
     */
    $this->addFieldMapping('tnid', NULL);
    $this->addFieldMapping(NULL, 'tnid');

    $this->addFieldMapping('translate', 'translate');

  }

  /**
   * Query for basic node fields from Drupal 7.
   *
   * @return QueryConditionInterface
   */
  protected function query() {
    $query = Database::getConnection('default', $this->sourceConnection)
             ->select('node', 'n')
             ->fields('n', array('nid', 'vid', 'language', 'title', 'uid',
               'status', 'created', 'changed', 'comment', 'promote', 'sticky',
               'tnid', 'translate'))
             ->condition('n.type', $this->sourceType)
             ->orderBy('n.changed');
    return $query;
  }
}
