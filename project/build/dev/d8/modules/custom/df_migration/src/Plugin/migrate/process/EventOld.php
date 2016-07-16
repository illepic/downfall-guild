<?php

/**
 * @file
 * Contains \Drupal\df_migration\Plugin\migrate\process\EventOld.
 */

namespace Drupal\df_migration\Plugin\migrate\process;

use Drupal\Core\Database\Database;
use Drupal\migrate\Annotation\MigrateProcessPlugin;
use Drupal\migrate\ProcessPluginBase;
use Drupal\migrate\MigrateExecutableInterface;
use Drupal\migrate\Row;

/**
 * Look up old d6 event start/end dates
 *
 * @MigrateProcessPlugin(
 *   id = "event_old"
 * )
 */
class EventOld extends ProcessPluginBase {

  protected function dateConvert($value) {
    // Create date object from the raw string in db. PHP handles this smart
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
    $nid = $value;
    $startend = $this->configuration['startend'];

    // Lookup in the d6 event table for just this nid
    $date = Database::getConnection('default', 'migrate')
      ->select('event', 'e')
      ->fields('e', array('event_start', 'event_end'))
      ->condition('nid', $nid)
      ->execute()
      ->fetchObject();

    return $startend == 'start' ? $this->dateConvert($date->event_start) : $this->dateConvert($date->event_end);
  }
}
