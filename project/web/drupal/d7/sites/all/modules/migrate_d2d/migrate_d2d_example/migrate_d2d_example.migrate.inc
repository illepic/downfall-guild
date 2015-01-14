<?php


/**
 * Implements hook_migrate_api().
 */
function migrate_d2d_example_migrate_api() {
  $api = array(
    'api' => 2,
    // Give the group a human-readable title
    'groups' => array(
      'example_group' => array(
        'title' => t('Example Group'),
      ),
    ),
  );
  return $api;
}
