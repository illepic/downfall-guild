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
    dpm($value);
    $pattern = "/\[img_assist(?:\\\\|\\\]|[^\]])*\]/"; // See http://rubular.com/r/gQs5HjGLok
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
      list($img, $offset_in_tmp) = $image_marker;

      // Strip off the first and last characters - they are [ and ].
      $img_pieces = substr($img, 1, -1);

      // Break the img_assist string into useful bits.
      // The dollar-underscore variable is a junk collector.
      // If there's a link on the image to an external URL,
      // there are 8 pieces in the tag, so we need to adjust variable assignments.
      if (count($pieces) == 8) {
        list($_, $nid, $title, $desc, $link, $url, $align, $width, $height) = explode("|", $img_pieces);
      }
      else {
        list($_, $nid, $title, $desc, $link, $align, $width, $height) = explode("|", $img_pieces);
      }

      list($_, $nid) = explode('=', $nid, 2);
      list($_, $title) = explode('=', $title, 2);
      list($_, $desc) = explode('=', $desc, 2);
      list($_, $link) = explode('=', $link, 2);
      list($_, $align) = explode('=', $align, 2);
      list($_, $width) = explode('=', $width, 2);
      list($_, $height) = explode('=', $height, 2);

      // Retrieve the image path from the image node.
      $image_path = self::getImagePath($nid);
      $image_tag = "<img alt=\"$desc\" src=\"$image_path\" style=\"width: ". $width ."px; height: ". $height ."px;\" class=\"align-". $align ."\">";

      // Add the link if it exists.
      if ($link && $url) {
        list($_, $url) = explode('=', $url, 2);
        $image_tag = '<a href="'. $url .'">' . $image_tag . '</a>';
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
    // Nuke those blank lines
    $value = str_replace('<p>&nbsp;</p>', '', $value);
    // Now replace images
    return $this->replaceImgAssistTags($value);
  }
}