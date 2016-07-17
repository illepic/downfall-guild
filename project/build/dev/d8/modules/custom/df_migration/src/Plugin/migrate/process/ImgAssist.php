<?php

/**
 * @file
 * Contains \Drupal\df_migration\Plugin\migrate\process\ImgAssist.
 */

namespace Drupal\df_migration\Plugin\migrate\process;

use Drupal\Core\Database\Database;
use Drupal\file\Entity\File;
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

    $images = self::getImageData($value);

    foreach($images as $attr) {

      $image_tag = "<img alt=\"{$attr['desc']}\" src=\"{$attr['path']}\" style=\"width\:{$attr['width']}px;height\:{$attr['height']}px;\" class=\"align-{$attr['align']}\">";

      // Add the link if it exists.
      if ($attr['url']) {
        $image_tag = "<a href=\"{$attr['url']}\">{$image_tag}</a>";
      }

      // Search through entire body, replace original token with new <img/>
      $value = str_replace($attr['marker'], $image_tag, $value);
    }

    return $value;
  }

  /**
   * Get an associative array of all the matches as keys
   *
   * @param $text_search
   * @return array
   */
  protected function getImageData($text_search) {
    $matches = self::findImgAssistTags($text_search);

    $images = [];
    foreach ($matches[0] as $image_marker) {
      list($original_img_assist_token) = $image_marker;

      // Strip off the first and last characters - they are [ and ].
      $pieces = substr($original_img_assist_token, 1, -1);

      // Array of all pieces, each looks like 'nid=1234'
      $pieces = explode('|', $pieces);
      // Remove the 'img_assist' string off the beginning
      array_shift($pieces);

      // Create array that transforms: array('nid=1234', 'title=', 'align=center')
      // to: array('nid' => '1234', 'title' => '', 'align' => 'center')
      $attr = [];
      foreach ($pieces as $piece) {
        list($piece_key, $piece_value) = explode('=', $piece);
        $attr[$piece_key] = $piece_value;
      }
      // Include the original string for use in replacements later
      $attr['marker'] = $original_img_assist_token;
      // Add path and fid to returned array
      list($attr['path'], $attr['fid']) = self::getImagePath($attr['nid']);
      $images[] = $attr;
    }

    // Return array of associative arrays
    return $images;
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
    $image = Database::getConnection('default', 'migrate')->query('SELECT fid FROM {image} WHERE nid=:nid AND image_size=:image_size', array(':nid' => $nid, ':image_size' => '_original'))->fetchObject();

    if ($image->fid) {
      // public://images/blah.jpg
      $drupal_file_uri = File::load($image->fid)->getFileUri();
      // /sites/default/files/images/blah.jpg
      $image_path = file_url_transform_relative(file_create_url($drupal_file_uri));

      return array($image_path, $image->fid);
    }
    // Sometimes there are entries without a corresponding node
    return array(null, null);

  }

  /**
   * Look up uploads on a node. Helps us consolidate all images on a node to the
   * primary image field
   *
   * @param $nid
   * @return array
   */
  private function extractUploads($nid) {
    $results = Database::getConnection('default', 'migrate')
      ->query('SELECT upload.fid
        FROM {upload} AS upload
        JOIN {node} AS node
          ON node.nid = upload.nid
        JOIN {files} AS files
          ON files.fid = upload.fid
        WHERE node.nid = :nid AND files.filemime LIKE :mime',
        array(':nid' => $nid, ':mime' => '%image%'))
      ->fetchAll();

    // EJECT NOW IF NO RESULTS
    if(empty($results)) {
      return array();
    }
    // Make a clean array
    $fids = array();
    foreach($results as $result) {
      // Verify this is real file
      if (File::load($result->fid)) {
        $fids[] = array('fid' => $result->fid);
      }
    }

    return $fids;
  }

  /**
   * {@inheritdoc}
   */
  public function transform($value, MigrateExecutableInterface $migrate_executable, Row $row, $destination_property) {
    $id = $value;

    // Different queries for comments vs nodes
    if($this->configuration['comment']) {
      $comment = Database::getConnection('default', 'migrate')
        ->query('SELECT comment FROM {comments} WHERE cid = :cid', array(':cid' => $id))
        ->fetchObject();
      $content = $comment->comment;
    } else {
      // Get node body for plugin
      $node = Database::getConnection('default', 'migrate')
        ->query('SELECT body FROM {node_revisions} WHERE nid = :nid', array(':nid' => $id))
        ->fetchObject();
      $content = $node->body;
    }

    // Now replace images (NOT DOING THIS ANYMORE)
    //return $this->replaceImgAssistTags($node->body);

    // Lookup image upload attachments
    $uploads = self::extractUploads($id);
    // Images in [img_assist] tags
    $images = self::getImageData($content);

    $fids = array_merge($uploads, $images);

    return $fids;

  }
}
