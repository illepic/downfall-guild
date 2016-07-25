<?php

/**
 * @file
 * Contains \Drupal\df_migration\Plugin\migrate\process\FidToMedia.
 */

namespace Drupal\df_migration\Plugin\migrate\process;

use Drupal\Core\Database\Database;
use Drupal\migrate\Annotation\MigrateProcessPlugin;
use Drupal\migrate\ProcessPluginBase;
use Drupal\migrate\MigrateExecutableInterface;
use Drupal\migrate\Row;

/**
 * This plugin looks up Drupal 6 Image node fids
 *
 * @MigrateProcessPlugin(
 *   id = "fid_to_media"
 * )
 */
class FidToMedia extends ProcessPluginBase {

  /**
   * {@inheritdoc}
   */
  public function transform($value, MigrateExecutableInterface $migrate_executable, Row $row, $destination_property) {

    var_dump($value);

    // Otherwise return media ids
    $fids_reduced = array($value);
    var_dump($fids_reduced);

    $query = \Drupal::entityQuery('media')
      ->condition('field_media_image_image.target_id', $fids_reduced, 'IN');
    $media = $query->execute();

    $mids = array_map(function($mid) { return array('mid' => $mid); }, array_values($media));
    var_dump($mids[0]['mid']);

    return array($mids[0]['mid']);
  }
}
