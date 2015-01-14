<?php

/**
 * @file
 * Wysiwyg API integration.
 */

/**
 * Implementation of hook_wysiwyg_plugin().
 */
function img_assist_img_assist_plugin() {
  $plugins = array();
  $plugins['img_assist'] = array(
    'title' => t('Image Assist'),
    'vendor url' => 'http://drupal.org/project/img_assist',
    'icon file' => 'img_assist.gif',
    'icon title' => t('Insert or update an embedded image'),
    'settings' => array(
      'dialog' => array(
        'url' => base_path() . 'index.php?q=img_assist/load/tinymce',
        'width' => 700,
        'height' => 500,
      ),
    ),
    // @todo Use a more granular way to validate contents for input formats.
    'extended_valid_elements' => array('img[class|src|border=0|alt|title|width|height|align|name|style]'),
  );
  return $plugins;
}

