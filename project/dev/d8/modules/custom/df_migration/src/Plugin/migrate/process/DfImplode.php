<?php

/**
 * @file
 * Contains \Drupal\df_migration\Plugin\migrate\process\Wat.
 */

namespace Drupal\df_migration\Plugin\migrate\process;

use Drupal\migrate\Annotation\MigrateProcessPlugin;
use Drupal\migrate\ProcessPluginBase;
use Drupal\migrate\MigrateExecutableInterface;
use Drupal\migrate\Row;

/**
 * Debug what's being sent down a process chain
 *
 * @MigrateProcessPlugin(
 *   id = "df_implode"
 * )
 */
class DfImplode extends ProcessPluginBase {

  /**
   * {@inheritdoc}
   */
  public function transform($value, MigrateExecutableInterface $migrate_executable, Row $row, $destination_property) {
    return implode($this->configuration['separator'], array_filter($value));
  }
}
