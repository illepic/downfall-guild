<?php
/**
 * @file
 * downfall_migrate_feature.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function downfall_migrate_feature_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "field_group" && $api == "field_group") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_node_info().
 */
function downfall_migrate_feature_node_info() {
  $items = array(
    'event' => array(
      'name' => t('event'),
      'base' => 'node_content',
      'description' => t('An event - raid, real life, or otherwise - can be made using this.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  return $items;
}
