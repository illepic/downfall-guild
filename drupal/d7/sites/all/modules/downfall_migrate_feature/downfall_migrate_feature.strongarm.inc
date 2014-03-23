<?php
/**
 * @file
 * downfall_migrate_feature.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function downfall_migrate_feature_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'file_public_path';
  $strongarm->value = 'sites/default/files';
  $export['file_public_path'] = $strongarm;

  return $export;
}
