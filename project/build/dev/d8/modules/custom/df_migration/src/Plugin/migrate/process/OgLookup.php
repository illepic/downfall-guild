<?php

/**
 * @file
 * Contains \Drupal\df_migration\Plugin\migrate\process\OgLookup.
 */

namespace Drupal\df_migration\Plugin\migrate\process;

use Drupal\Core\Database\Database;
use Drupal\migrate\Annotation\MigrateProcessPlugin;
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

    // Lookup old taxonomy terms for old raids and match to group ids
    $termgroup = array(
      '3' => '12359', // Hamfist
      '4' => '12360', # LF1M, Group Ref: 12360
      '60' => '7393', # Lava Crab, Group Ref: 7393
      '62' => '10671', # GPS, Group Ref: 10671
      '78' => '8056', # mALT, Group Ref: 8056
      '89' => '7365', # Kitten Brigade, Group Ref: 7365
      '90' => '6593', # Salmon, Group Ref: 6593
      '100' => '12361', # PMS, Group Ref: 12361
      '101' => '9406', # Happy Ending, Group Ref: 9406
      '15' => '12359', # Hamfist tag, Group Ref: 12359
      '16' => '12360', # LF1M, Group Ref: 12360
      '96' => '7365', # Kitten Brigade, group ref: 7365
      '97' => '6593', # Salmon, group ref: 6593
      '98' => '7393', # Lava Crab, group ref: 7393
    );

    // If our nid has any of the above tid's, then tag with associated Group (dedupe groups)
    $tids = array_keys($termgroup);
    $groups = Database::getConnection('default', 'migrate')->query('SELECT * FROM {term_node} WHERE nid=:nid AND tid IN (:tids[])', array(':nid' => $value, ':tids[]' => $tids))->fetchAll();

    // Lookup in our table
    foreach($groups as $group) {
      $node_refs[] = $termgroup[$group->tid];
    }
    // Dedupe
    $node_refs = array_unique($node_refs);

    // Return an array of nid's to make the node reference here
    return $node_refs;
  }
}
