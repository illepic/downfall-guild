<?php
/**
 * @file
 * downfall_migrate_feature.features.taxonomy.inc
 */

/**
 * Implements hook_taxonomy_default_vocabularies().
 */
function downfall_migrate_feature_taxonomy_default_vocabularies() {
  return array(
    'forums' => array(
      'name' => 'Forums',
      'machine_name' => 'forums',
      'description' => 'Forum navigation vocabulary',
      'hierarchy' => 1,
      'module' => 'forum',
      'weight' => -10,
    ),
    'gallery' => array(
      'name' => 'Gallery',
      'machine_name' => 'gallery',
      'description' => 'gallery',
      'hierarchy' => 0,
      'module' => 'taxonomy',
      'weight' => 0,
    ),
    'wow' => array(
      'name' => 'WoW',
      'machine_name' => 'wow',
      'description' => 'All the WoW-related tags.',
      'hierarchy' => 0,
      'module' => 'taxonomy',
      'weight' => 0,
    ),
  );
}
