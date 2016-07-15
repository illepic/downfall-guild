<?php

/**
 * @file
 * Contains \Drupal\df_migration\Plugin\migrate\process\ImgAssist.
 */

namespace Drupal\df_migration\Plugin\migrate\process;

use Drupal\Core\Database\Database;
use Drupal\migrate\ProcessPluginBase;
use Drupal\migrate\MigrateExecutableInterface;
use Drupal\migrate\Row;

/**
 * This plugin replaces img_assist tags in node body fields with standard HTML image tags.
 *
 * @MigrateProcessPlugin(
 *   id = "img_assist"
 * )
 */
class ImgAssist extends ProcessPluginBase {

  /**
   * Find and return image assist tags.
   *
   * @param string $value string of text to search for image assist tags
   *
   * @return array $matches array of matched strings
   */
  protected function findImgAssistTags($value) {

    $pattern = "/\[img_assist(?:\\\\|\\\]|[^\]])*\]/"; // See http://regexr.com/3dqmc
    preg_match_all($pattern, $value, $matches, PREG_OFFSET_CAPTURE); // The PREG_OFFSET_CAPTURE gives us the offset_in_tmp variable.
    return $matches;
  }

  /**
   * Replace image assist tags with HTML image tags.
   *
   * @param string $value string of text to search for image assist tags
   *
   * @return array $matches array of matched strings
   */
  protected function replaceImgAssistTags($value) {
    $matches = self::findImgAssistTags($value);

    foreach ($matches[0] as $image_marker) {
      list($img) = $image_marker;

      // Strip off the first and last characters - they are [ and ].
      $pieces = substr($img, 1, -1);

      // Array of all pieces, each looks like 'nid=1234'
      $pieces = explode('|', $pieces);
      // Remove the 'img_assist' string off the beginning
      array_shift($pieces);

      // Create array that transforms: array('nid=1234', 'title=', 'align=center')
      // to: array('nid' => '1234', 'title' => '', 'align' => 'center')
      $attr = [];
      foreach($pieces as $piece) {
        list($piece_key, $piece_value) = explode('=', $piece);
        $attr[$piece_key] = $piece_value;
      }

      // Retrieve the image path from the image node.
      $image_path = self::getImagePath($attr['nid']);

      $image_tag = "<img alt=\"{$attr['desc']}\" src=\"{$image_path}\" style=\"width\:{$attr['width']}px;height\:{$attr['height']}px;\" class=\"align-{$attr['align']}\">";

      // Add the link if it exists.
      if ($attr['url']) {
        $image_tag = "<a href=\"{$attr['url']}\">{$image_tag}</a>";
      }

      $value = str_replace($img, $image_tag, $value);
    }

    return $value;
  }

  /**
   * Look up an image file path by its node ID.
   *
   * @param int $nid an image node ID
   *
   * @return string $image_path
   */
  private function getImagePath($nid) {

    // Look up the node referenced by the img_assist tag, then grab the image file ID from that node.
    $image = Database::getConnection('default', 'migrate')->query('SELECT * FROM {image} WHERE nid=:nid AND image_size=:image_size', array(':nid' => $nid, ':image_size' => '_original'))->fetchObject();

    // Get the image path from the image file ID.
    $file = Database::getConnection('default', 'migrate')->query('SELECT * FROM {files} WHERE fid=:fid', array(':fid' => $image->fid))->fetchObject();

    // Remove the 'www.downfallguild.org' sub folder, replace with default
    $path = str_replace('www.downfallguild.org', 'default', $file->filepath);

    // Instead look up public file path here

    // Add a beginning slash to the path.
    $image_path = '/' . $path;

    return $image_path;
  }

  /**
   * {@inheritdoc}
   */
  public function transform($value, MigrateExecutableInterface $migrate_executable, Row $row, $destination_property) {
    $replace = $this->configuration['replace'];

    if ($replace) {
      // Nuke those blank lines
      $value = str_replace('<p>&nbsp;</p>', '', $value); // Move this kind of stuff to it's own plugin
      // Now replace images
      return $this->replaceImgAssistTags($value);
    }
    else {
      return $value; // Change this to return the fids
    }

  }
}
