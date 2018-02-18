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
 *   id = "empty_if_matches"
 * )
 */
class EmptyIfMatches extends ProcessPluginBase {

  /**
   * {@inheritdoc}
   */
  public function transform($value, MigrateExecutableInterface $migrate_executable, Row $row, $destination_property) {

    return ($value[0] == $value[1]) ? '' : $value[0];
  }
}
