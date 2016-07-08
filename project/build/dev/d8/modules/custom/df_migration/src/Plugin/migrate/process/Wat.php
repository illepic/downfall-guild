<?php

/**
 * @file
 * Contains \Drupal\df_migration\Plugin\migrate\process\Wat.
 */

namespace Drupal\df_migration\Plugin\migrate\process;

use Drupal\migrate\ProcessPluginBase;
use Drupal\migrate\MigrateExecutableInterface;
use Drupal\migrate\Row;

/**
 * Debug what's being sent down a process chain
 *
 * @MigrateProcessPlugin(
 *   id = "wat"
 * )
 */
class Wat extends ProcessPluginBase {

  /**
   * {@inheritdoc}
   */
  public function transform($value, MigrateExecutableInterface $migrate_executable, Row $row, $destination_property) {
    var_dump($value);
//    var_dump($this);
//    print_r($this->configuration['debug']);

    return $value;
  }
}
