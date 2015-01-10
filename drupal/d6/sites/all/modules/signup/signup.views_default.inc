<?php
// $Id$
/**
 * @file
 * Contains default views on behalf of the signup module
 */

/**
 * Implementation of hook_views_default_views().
 */
function signup_views_default_views() {
  // Signup schedule at user/N/signups and the "Current signups" block.
  $view = new view;
  $view->name = 'signup_current_signups';
  $view->description = t('A list of all signups for the current user');
  $view->tag = 'signups';
  $view->view_php = '';
  $view->base_table = 'node';
  $view->is_cacheable = FALSE;
  $view->api_version = 2;
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */
    // Default Display
    $display = new views_display;
    $display->id = 'default';
    $display->display_title = t('Defaults');
    $display->display_plugin = 'default';
    $display->position = 1;
    $display->display_options = array(
      'relationships' => array(),
      'fields' =>  array(
        'title' => array(
          'label' => 'Title',
          'link_to_node' => 1,
          'exclude' => 0,
          'id' => 'title',
          'table' => 'node',
          'field' => 'title',
          'relationship' => 'none',
        ),
      ),
      'arguments' => array(
        'signup_uid' => array(
          'default_action' => 'not found',
          'style_plugin' => 'default_summary',
          'style_options' => array(),
          'wildcard' => '',
          'wildcard_substitution' => '',
          'title' => '',
          'default_argument_type' => 'fixed',
          'default_argument' => '',
          'validate_type' => 'none',
          'validate_fail' => 'not found',
          'break_phrase' => 0,
          'not' => 0,
          'id' => 'signup_uid',
          'table' => 'signup_log',
          'field' => 'signup_uid',
          'relationship' => 'none',
          'default_options_div_prefix' => '',
          'default_argument_user' => 0,
          'default_argument_fixed' => '',
          'default_argument_php' => '',
          'validate_argument_node_type' => array(
            'event' => 0,
            'page' => 0,
            'story' => 0,
          ),
          'validate_argument_node_access' => 0,
          'validate_argument_nid_type' => 'nid',
          'validate_argument_vocabulary' => array(),
          'validate_argument_type' => 'tid',
          'validate_argument_php' => '',
        ),
      ),
      'title' => t('Current Signups'),
      'style_plugin' =>  'list',
      'style_options' => array(),
      'empty' => t('This user has not signed up for any content.'),
      'empty_format' => '1',
      'use_pager' => '1',
      'use_more' => 1,
      'items_per_page' => 20,
    );
    if (module_exists('php')) {
      $display->display_options['footer'] = '<?php global $user; print l(t("View signup schedule"), "user/$user->uid/signups"); ?>';
      $display->display_options['footer_format'] = '3';
    }
  $view->display['default'] = $display;
    $display = new views_display;
    $display->id = 'page';
    $display->display_title = t('Page');
    $display->display_plugin = 'page';
    $display->position = 2;
    $display->display_options = array(
      'defaults' => array(
        'access' => TRUE,
        'title' => TRUE,
        'header' => TRUE,
        'header_format' => TRUE,
        'header_empty' => TRUE,
        'footer' => TRUE,
        'footer_format' => TRUE,
        'footer_empty' => TRUE,
        'empty' => TRUE,
        'empty_format' => TRUE,
        'use_ajax' => TRUE,
        'offset' => TRUE,
        'use_pager' => TRUE,
        'pager_element' => TRUE,
        'use_more' => TRUE,
        'distinct' => TRUE,
        'link_display' => TRUE,
        'style_plugin' => TRUE,
        'style_options' => TRUE,
        'row_plugin' => TRUE,
        'row_options' => TRUE,
        'relationships' => TRUE,
        'fields' => TRUE,
        'sorts' => TRUE,
        'arguments' => TRUE,
        'filters' => TRUE,
      ),
      'use_pager' => '1',
      'path' => 'usr/%/signups/current',
      'menu' => array(
        'type' => 'default tab',
        'title' => 'Current',
        'weight' => '-2',
      ),
      'tab_options' => array(
        'type' => 'tab',
        'title' => 'Signups',
        'weight' => '10',
      ),
    );
  $view->display['page'] = $display;
    $display = new views_display;
    $display->id = 'block';
    $display->display_title = t('Block');
    $display->display_plugin = 'block';
    $display->position = '3';
    $display->display_options = array(
      'defaults' => array(
        'access' => TRUE,
        'title' => TRUE,
        'header' => TRUE,
        'header_format' => TRUE,
        'header_empty' => TRUE,
        'footer' => TRUE,
        'footer_format' => TRUE,
        'footer_empty' => TRUE,
        'empty' => TRUE,
        'empty_format' => TRUE,
        'use_ajax' => TRUE,
        'offset' => TRUE,
        'use_pager' => TRUE,
        'pager_element' => TRUE,
        'items_per_page' => FALSE,
        'use_more' => TRUE,
        'distinct' => TRUE,
        'link_display' => TRUE,
        'style_plugin' => TRUE,
        'style_options' => TRUE,
        'row_plugin' => TRUE,
        'row_options' => TRUE,
        'relationships' => TRUE,
        'fields' => TRUE,
        'sorts' => TRUE,
        'arguments' => TRUE,
        'filters' => TRUE,
      ),
      'items_per_page' => 10,
      'arguments' => array(
        'signup_uid' => array(
          'default_action' => 'default',
          'style_plugin' => 'default_summary',
          'style_options' => array(),
          'wildcard' => '',
          'wildcard_substitution' => '',
          'title' => '',
          'default_argument_type' => 'php',
          'default_argument' => '',
          'validate_type' => 'none',
          'validate_fail' => 'not found',
          'break_phrase' => 0,
          'not' => 0,
          'id' => 'signup_uid',
          'table' => 'signup_log',
          'field' => 'signup_uid',
          'relationship' => 'none',
          'default_options_div_prefix' => '',
          'default_argument_user' => 0,
          'default_argument_fixed' => '',
          'default_argument_php' => 'global $user; return $user->uid;',
          'validate_argument_node_type' => array(
            'event' => 0,
            'page' => 0,
            'story' => 0,
          ),
          'validate_argument_node_access' => 0,
          'validate_argument_nid_type' => 'nid',
          'validate_argument_vocabulary' => array(),
          'validate_argument_type' => 'tid',
          'validate_argument_php' => '',
          'override' => array(
            'button' => 'Use default',
          ),
        ),
    ));
  $view->display['block'] = $display;
  $views[$view->name] = $view;

  // Subtab of user/N/signups for all signup-enabled nodes that the
  // user hasn't replied to and the "Available signups" block.
  $view = new view;
  $view->name = 'signup_available_signups';
  $view->description = t('A view of all available signups (signup-enabled content the user has not replied to).');
  $view->tag = 'signups';
  $view->view_php = '';
  $view->base_table = 'node';
  $view->is_cacheable = FALSE;
  $view->api_version = 2;
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */
  $display = new views_display;
    $display->id = 'default';
    $display->display_title = t('Defaults');
    $display->display_plugin = 'default';
    $display->position = '1';
    $display->display_options = array(
      'fields' => array(
        'title' => array(
          'label' => 'Title',
          'link_to_node' => 1,
          'exclude' => 0,
          'id' => 'title',
          'table' => 'node',
          'field' => 'title',
          'relationship' => 'none',
        ),
      ),
      'arguments' => array(
        'signup_uid' => array(
          'default_action' => 'not found',
          'style_plugin' => 'default_summary',
          'style_options' => array(),
          'wildcard' => '',
          'wildcard_substitution' => '',
          'title' => '',
          'default_argument_type' => 'fixed',
          'default_argument' => '',
          'validate_type' => 'none',
          'validate_fail' => 'not found',
          'break_phrase' => 0,
          'not' => 0,
          'id' => 'signup_uid',
          'table' => 'signup_log',
          'field' => 'signup_uid',
          'relationship' => 'none',
          'default_options_div_prefix' => '',
          'default_argument_user' => 0,
          'default_argument_fixed' => '',
          'default_argument_php' => '',
          'validate_argument_node_type' => array(
            'event' => 0,
            'page' => 0,
            'story' => 0,
          ),
          'validate_argument_node_access' => 0,
          'validate_argument_nid_type' => 'nid',
          'validate_argument_vocabulary' => array(),
          'validate_argument_type' => 'tid',
          'validate_argument_php' => '',
          'not_signed_up' => 1,
        ),
      ),
      'filters' => array(
        'status' => array(
          'operator' => '=',
          'value' => 1,
          'group' => '0',
          'exposed' => FALSE,
          'expose' => array(
            'operator' => FALSE,
            'label' => '',
          ),
          'id' => 'status',
          'table' => 'signup',
          'field' => 'status',
          'relationship' => 'none',
        ),
      ),
      'title' => t('Available signups'),
      'empty' => t('Congratulations, you have replied to all of the content on the site that is accepting signups.'),
      'empty_format' => '1',
      'items_per_page' => 20,
      'use_pager' => '1',
      'use_more' => 1,
      'style_plugin' => 'list',
      'style_options' => array(
        'type' => 'ul',
      ),
    );
  $view->display['default'] = $display;
    $display = new views_display;
    $display->id = 'page';
    $display->display_title = t('Page');
    $display->display_plugin = 'page';
    $display->position = '2';
    $display->display_options = array(
      'defaults' => array(
        'access' => TRUE,
        'title' => TRUE,
        'header' => TRUE,
        'header_format' => TRUE,
        'header_empty' => TRUE,
        'footer' => TRUE,
        'footer_format' => TRUE,
        'footer_empty' => TRUE,
        'empty' => TRUE,
        'empty_format' => TRUE,
        'use_ajax' => TRUE,
        'items_per_page' => TRUE,
        'offset' => TRUE,
        'use_pager' => TRUE,
        'pager_element' => TRUE,
        'use_more' => TRUE,
        'distinct' => TRUE,
        'link_display' => TRUE,
        'style_plugin' => TRUE,
        'style_options' => TRUE,
        'row_plugin' => TRUE,
        'row_options' => TRUE,
        'relationships' => TRUE,
        'fields' => TRUE,
        'sorts' => TRUE,
        'arguments' => TRUE,
        'filters' => TRUE,
      ),
      'path' => 'user/%/signups/available',
      'menu' => array(
        'type' => 'tab',
        'title' => 'Available',
        'weight' => '10',
      ),
      'tab_options' => array(
        'type' => 'none',
        'title' => '',
        'weight' => 0,
      ),
    );
  $view->display['page'] = $display;
    $display = new views_display;
    $display->id = 'block';
    $display->display_title = t('Block');
    $display->display_plugin = 'block';
    $display->position = '3';
    $display->display_options = array(
      'defaults' => array(
        'access' => TRUE,
        'title' => TRUE,
        'header' => TRUE,
        'header_format' => TRUE,
        'header_empty' => TRUE,
        'footer' => TRUE,
        'footer_format' => TRUE,
        'footer_empty' => TRUE,
        'empty' => TRUE,
        'empty_format' => TRUE,
        'use_ajax' => TRUE,
        'items_per_page' => FALSE,
        'offset' => TRUE,
        'use_pager' => TRUE,
        'pager_element' => TRUE,
        'use_more' => TRUE,
        'distinct' => TRUE,
        'link_display' => TRUE,
        'style_plugin' => TRUE,
        'style_options' => TRUE,
        'row_plugin' => TRUE,
        'row_options' => TRUE,
        'relationships' => TRUE,
        'fields' => TRUE,
        'sorts' => TRUE,
        'arguments' => TRUE,
        'filters' => TRUE,
      ),
      'items_per_page' => 10,
      'arguments' => array(
        'signup_uid' => array(
          'default_action' => 'default',
          'style_plugin' => 'default_summary',
          'style_options' => array(),
          'wildcard' => '',
          'wildcard_substitution' => '',
          'title' => '',
          'default_argument_type' => 'php',
          'default_argument' => '',
          'validate_type' => 'none',
          'validate_fail' => 'not found',
          'break_phrase' => 0,
          'not' => 0,
          'id' => 'signup_uid',
          'table' => 'signup_log',
          'field' => 'signup_uid',
          'relationship' => 'none',
          'default_options_div_prefix' => '',
          'default_argument_user' => 0,
          'default_argument_fixed' => '',
          'default_argument_php' => 'global $user; return array(0 => $user->uid);',
          'validate_argument_node_type' => array(
            'event' => 0,
            'page' => 0,
            'story' => 0,
          ),
          'validate_argument_node_access' => 0,
          'validate_argument_nid_type' => 'nid',
          'validate_argument_vocabulary' => array(),
          'validate_argument_type' => 'tid',
          'validate_argument_php' => '',
          'override' => array(
            'button' => 'Use default',
          ),
        ),
      ),
    );
  $view->display['block'] = $display;
  $views[$view->name] = $view;

  return $views;
}
