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
  $file_display->name = 'image__df_teaser__file_field_image';
  $file_display->weight = 0;
  $file_display->status = TRUE;
  $file_display->settings = array(
    'image_style' => 'image_900',
    'image_link' => 'content',
  );
  $export['image__df_teaser__file_field_image'] = $file_display;

  return $export;
}
