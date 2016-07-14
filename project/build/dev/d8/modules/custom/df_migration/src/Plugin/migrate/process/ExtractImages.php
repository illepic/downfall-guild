<?php

/**
 * @file
 * Contains \Drupal\df_migration\Plugin\migrate\process\ExtractImages.
 */

namespace Drupal\df_migration\Plugin\migrate\process;

use Drupal\Core\Database\Database;
use Drupal\migrate\ProcessPluginBase;
use Drupal\migrate\MigrateExecutableInterface;
use Drupal\migrate\Row;

/**
 * Lookup taxonomy terms by nid and specific vocabulary
 *
 * @MigrateProcessPlugin(
 *   id = "extract_images"
 * )
 */
class ExtractImages extends ProcessPluginBase {

  /**
   * {@inheritdoc}
   */
  public function transform($value, MigrateExecutableInterface $migrate_executable, Row $row, $destination_property) {
    $nid = $value;

    $results = Database::getConnection('default', 'migrate')
      ->query('SELECT fid FROM {upload} WHERE nid = :nid', array(':nid' => $nid))
      ->fetchAll();

    // EJECT NOW IF NO RESULTS
    if(empty($results)) {
      return array();
    }

    // Make a clean array
    $fids = array();
    foreach($results as $result) {
      $fids[] = $result->fid;
    }

    var_dump($nid);
    var_dump($fids);

    return $fids;
  }
}
