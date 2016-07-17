<?php

/**
 * @file
 * Contains \Drupal\df_migration\Plugin\migrate\process\RemoveStrings.
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
 *   id = "remove_strings"
 * )
 */
class RemoveStrings extends ProcessPluginBase {

  protected function killImgAssistTags($value) {

    $pattern = "/\[img_assist(?:\\\\|\\\]|[^\]])*\]/"; // See http://regexr.com/3dqmc
    preg_match_all($pattern, $value, $matches, PREG_OFFSET_CAPTURE); // The PREG_OFFSET_CAPTURE gives us the offset_in_tmp variable.

    foreach($matches[0] as $image_marker) {
      list($img_assist_token) = $image_marker;
      $value = str_replace($img_assist_token, '', $value);
    }

    return $value;
  }

  /**
   * {@inheritdoc}
   */
  public function transform($value, MigrateExecutableInterface $migrate_executable, Row $row, $destination_property) {

    $value = self::killImgAssistTags($value);
    $value = str_replace('<p>&nbsp;</p>', '', $value);
    $value = str_replace('<p></p>', '', $value);
    $value = str_replace('&nbsp;', '', $value);
    $value = str_replace('<p><img src="http://armory.mmo-champion.com.nyud.net:8080/sig.php/1486310TkEWU.png" /></p>', '', $value);
    $value = preg_replace("/(\r?\n){2,}/", '', $value); // kill the extra breaks

    return $value;
  }
}
