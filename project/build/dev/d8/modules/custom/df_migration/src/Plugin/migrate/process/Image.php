<?php

/**
 * @file
 * Contains \Drupal\df_migration\Plugin\migrate\process\Image.
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
 *   id = "image"
 * )
 */
class Image extends ProcessPluginBase {

  /**
   * {@inheritdoc}
   */
  public function transform($value, MigrateExecutableInterface $migrate_executable, Row $row, $destination_property) {

    // Within the D6 Image table, find the D6 fid and return it
    $image = Database::getConnection('default', 'migrate')->query('SELECT * FROM {image} WHERE nid=:nid AND image_size=:image_size', array(':nid' => $value, ':image_size' => '_original'))->fetchObject();

    if($this->configuration['type'] == 'fid') {
      // Return the D6 fid (so this can be part of a Migrate process chain)
      return $image->fid;
    }

    // Otherwise return media ids
    $fids_reduced = array($image->fid);

    $query = \Drupal::entityQuery('media')
      ->condition('field_media_image_image.target_id', $fids_reduced, 'IN');
    $media = $query->execute();

    $mids = array_map(function($fid) { return array('fid' => $fid); }, array_values($media));

    return $mids;

  }
}
