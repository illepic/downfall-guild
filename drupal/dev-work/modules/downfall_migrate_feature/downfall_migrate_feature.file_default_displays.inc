<?php
/**
 * @file
 * downfall_migrate_feature.file_default_displays.inc
 */

/**
 * Implements hook_file_default_displays().
 */
function downfall_migrate_feature_file_default_displays() {
  $export = array();

  $file_display = new stdClass();
  $file_display->api_version = 1;
  $file_display->name = 'image__default__file_image';
  $file_display->weight = -49;
  $file_display->status = TRUE;
  $file_display->settings = array(
    'image_style' => 'large',
    'alt' => 'tst',
    'title' => 'testt',
  );
  $export['image__default__file_image'] = $file_display;

  $file_display = new stdClass();
  $file_display->api_version = 1;
  $file_display->name = 'image__teaser__file_image';
  $file_display->weight = 5;
  $file_display->status = TRUE;
  $file_display->settings = array(
    'image_style' => 'square_thumbnail',
    'alt' => '',
    'title' => '',
  );
  $export['image__teaser__file_image'] = $file_display;

  return $export;
}
