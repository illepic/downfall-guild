<?php

/**
 * @file
 * Contains \Drupal\df_migration\Plugin\migrate\process\ExtractUploads.
 */

namespace Drupal\df_migration\Plugin\migrate\process;

use Drupal\Core\Database\Database;
use Drupal\migrate\Annotation\MigrateProcessPlugin;
use Drupal\migrate\ProcessPluginBase;
use Drupal\migrate\MigrateExecutableInterface;
use Drupal\migrate\Row;

/**
 * Lookup taxonomy terms by nid and specific vocabulary
 *
 * @MigrateProcessPlugin(
 *   id = "extract_uploads"
 * )
 */
class ExtractUploads extends ProcessPluginBase {

  /**
   * {@inheritdoc}
   */
  public function transform($value, MigrateExecutableInterface $migrate_executable, Row $row, $destination_property) {
    $nid = $value;
    $mime = $this->configuration['mime'];
    $like = $this->configuration['like'];

    // Lookup on this et
    $results = Database::getConnection('default', 'migrate')
      ->query('SELECT upload.fid
        FROM {upload} AS upload
        JOIN {node} AS node
          ON node.nid = upload.nid
        JOIN {files} AS files
          ON files.fid = upload.fid
        WHERE node.nid = :nid AND files.filemime ' . $like . ' :mime',
        array(':nid' => $nid, ':mime' => '%' . $mime . '%'))
      ->fetchAll();

    // EJECT NOW IF NO RESULTS
    if(empty($results)) {
      return array();
    }

    // Make a clean array
    $fids = array();
    foreach($results as $result) {
      $fids[] = array('fid' => $result->fid);
    }

    var_dump('nid:', $nid, 'fids:', $fids);

    return $fids;
  }
}
