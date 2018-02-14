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
 *   id = "skip_contains"
 * )
 */
class SkipContains extends ProcessPluginBase {

  // Simple check if array of needles is in haystack
  public function containCheck($haystack, $needles) {
    foreach ($needles as $needle) {
      if (stripos(strtolower($haystack), strtolower($needle)) !== false) return true;
    }
    return false;
  }

  /**
   * {@inheritdoc}
   */
  public function transform($value, MigrateExecutableInterface $migrate_executable, Row $row, $destination_property) {

    $found = $this->containCheck($value, $this->configuration['skip']);

    // If anything found, return false, otherwise return original value
    return ($found) ? false : $value;
  }
}
