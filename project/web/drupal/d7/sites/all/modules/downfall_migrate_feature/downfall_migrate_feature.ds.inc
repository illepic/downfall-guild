<?php
/**
 * @file
 * downfall_migrate_feature.ds.inc
 */

/**
 * Implements hook_ds_view_modes_info().
 */
function downfall_migrate_feature_ds_view_modes_info() {
  $export = array();

  $ds_view_mode = new stdClass();
  $ds_view_mode->api_version = 1;
  $ds_view_mode->view_mode = 'df_teaser';
  $ds_view_mode->label = 'df_teaser';
  $ds_view_mode->entities = array(
    'file' => 'file',
  );
  $export['df_teaser'] = $ds_view_mode;

  return $export;
}
