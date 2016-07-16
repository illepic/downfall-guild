<?php

/**
 * @file
 * Contains \Drupal\df_migration\Plugin\migrate\process\ImagePath.
 */

namespace Drupal\df_migration\Plugin\migrate\process;

use Drupal\Core\Database\Database;
use Drupal\migrate\Annotation\MigrateProcessPlugin;
use Drupal\migrate\ProcessPluginBase;
use Drupal\migrate\MigrateExecutableInterface;
use Drupal\migrate\Row;

/**
 * This plugin fixes d6 Image file names to be the actual filename from filesystem
 *
 * @MigrateProcessPlugin(
 *   id = "image_path"
 * )
 */
class ImagePath extends ProcessPluginBase {

  /**
   * {@inheritdoc}
   */
  public function transform($value, MigrateExecutableInterface $migrate_executable, Row $row, $destination_property) {
    return basename($value);
  }
}
