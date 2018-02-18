<?php

/**
 * @file
 * Contains \Drupal\df_migration\Plugin\migrate\process\RejectFound.
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
 *   id = "reject_found"
 * )
 */
class RejectFound extends ProcessPluginBase {

  /**
   * {@inheritdoc}
   */
  public function transform($value, MigrateExecutableInterface $migrate_executable, Row $row, $destination_property) {
    $source = $row->getSource();
    $return = $this->configuration['return'] ?? 'nid';

    if (is_null($value)) {
      print_r("Value is null (not found in prior step). {$return}: {$source[$return]} will be passed along." . PHP_EOL);
      return $source[$return];
    }
    else {
      print_r("ID (not necessarily nid) {$value} was found in prior lookup. Empty will be returned to skip." . PHP_EOL);
      return '';
    }
  }
}
