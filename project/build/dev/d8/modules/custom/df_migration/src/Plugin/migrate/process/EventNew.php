<?php

/**
 * @file
 * Contains \Drupal\df_migration\Plugin\migrate\process\EventNew.
 */

namespace Drupal\df_migration\Plugin\migrate\process;

use Drupal\migrate\Annotation\MigrateProcessPlugin;
use Drupal\migrate\ProcessPluginBase;
use Drupal\migrate\MigrateExecutableInterface;
use Drupal\migrate\Row;

/**
 * Look up old d6 event start/end dates
 *
 * @MigrateProcessPlugin(
 *   id = "event_new"
 * )
 */
class EventNew extends ProcessPluginBase {

  protected function dateConvert($value) {
    // Create date object from the raw sting in db. PHP handles this smart
    $date = new \DateTime($value, new \DateTimeZone('America/Los_Angeles'));
    // Drupal stores all time in UTC, convert
    $date->setTimezone(new \DateTimeZone('UTC'));
    // We need the format 2015-09-18T18:30:00
    return $date->format('Y-m-d\TH:i:s');
  }
  /**
   * {@inheritdoc}
   */
  public function transform($value, MigrateExecutableInterface $migrate_executable, Row $row, $destination_property) {
    return $this->dateConvert($value);
  }
}
