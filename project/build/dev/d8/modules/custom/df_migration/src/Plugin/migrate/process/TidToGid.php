<?php

/**
 * @file
 * Contains \Drupal\df_migration\Plugin\migrate\process\SkipContains.
 */

namespace Drupal\df_migration\Plugin\migrate\process;

use Drupal\migrate\Annotation\MigrateProcessPlugin;
use Drupal\migrate\ProcessPluginBase;
use Drupal\migrate\MigrateExecutableInterface;
use Drupal\migrate\Row;

/**
 * Return null if $value contains any of the values sent over
 *
 * @MigrateProcessPlugin(
 *   id = "tid_to_gid"
 * )
 */
class TidToGid extends ProcessPluginBase {

  /**
   * {@inheritdoc}
   */
  public function transform($value, MigrateExecutableInterface $migrate_executable, Row $row, $destination_property) {

    $tid = $this->configuration['tid'];
    $gid = $this->configuration['gid'];


//    var_dump($row);

    if ($gid) {
      return $gid;
    }
    else {
      $tid_gid_map = $row['tid_gid_map'];
      var_dump($tid_gid_map);
    }

  }
}
