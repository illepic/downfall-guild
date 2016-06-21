<?php

/**
 * @file
 * Contains \Drupal\df_migration\Plugin\migrate\process\OgLookup.
 */

namespace Drupal\df_migration\Plugin\migrate\process;

use Drupal\Core\Database\Database;
use Drupal\migrate\ProcessPluginBase;
use Drupal\migrate\MigrateExecutableInterface;
use Drupal\migrate\Row;

/**
 * This plugin fixes d6 Image file names to be the actual filename from filesystem
 *
 * @MigrateProcessPlugin(
 *   id = "og_lookup"
 * )
 */
class OgLookup extends ProcessPluginBase {

  /**
   * {@inheritdoc}
   */
  public function transform($value, MigrateExecutableInterface $migrate_executable, Row $row, $destination_property) {
    // Lookup in og_uid table all mentions of $value (nid)
    $groups = Database::getConnection('default', 'migrate')->query('SELECT group_nid FROM {og_ancestry} WHERE nid=:nid', array(':nid' => $value))->fetchAll();

    // Loop over the group node ids returned, and make the a single dimension array
    $node_refs = array();
    foreach($groups as $group) {
      $node_refs[] = $group->group_nid;
    }

    // Return an array of nid's to make the node reference here
    return $node_refs;
  }
}
