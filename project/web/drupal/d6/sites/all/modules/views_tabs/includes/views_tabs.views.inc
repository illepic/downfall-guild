<?php

function views_tabs_views_handlers() {
  return array(
    'info' => array(
      'path' => drupal_get_path('module', 'views_tabs') .'/includes',
    ),
    'handlers' => array(
      'views_tabs_plugin_style' => array(
        'parent' => 'views_plugin_style',
      ),
    ),
  );
}

/**
 *  Implementation of hook_views_style_plugins()
 */
function views_tabs_views_plugins() {
  $plugins = array(
    'style' => array(
      'views_tabs' => array(
        'title' => t('Views Tabs'),
        'help' => t('Output results to tabs'),
        'handler' => 'views_tabs_plugin_style',
        'path' => drupal_get_path('module', 'views_tabs') . '/includes',
        'uses row plugin' => TRUE,
        'uses options' => TRUE,
        'uses grouping' => TRUE,
        'type' => 'normal',
      ),
    ),
  );
  return $plugins;
}
