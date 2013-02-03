<?php
/**
 * @file
 * downfall_migrate_feature.features.filter.inc
 */

/**
 * Implements hook_filter_default_formats().
 */
function downfall_migrate_feature_filter_default_formats() {
  $formats = array();

  // Exported format: Raw Input.
  $formats['raw_input'] = array(
    'format' => 'raw_input',
    'name' => 'Raw Input',
    'cache' => '1',
    'status' => '1',
    'weight' => '0',
    'filters' => array(
      'filter_htmlcorrector' => array(
        'weight' => '10',
        'status' => '1',
        'settings' => array(),
      ),
    ),
  );

  return $formats;
}
