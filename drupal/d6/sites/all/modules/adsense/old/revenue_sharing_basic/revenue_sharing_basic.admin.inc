<?php

/**
 * @file
 * Contains the administrative functions of the revenue_sharing_basic
 * module.
 *
 * This file is included by the basic revenue sharing  module, and includes
 * the settings form.
 */

/**
 * Menu callback for the revenue_sharing_basic module settings form.
 *
 * @ingroup forms
 */
function revenue_sharing_basic_settings() {
  module_load_include('inc', 'revenue_sharing_basic', 'help/revenue_sharing_basic.help');

  $form['help'] = array(
    '#type'        => 'fieldset',
    '#collapsible' => TRUE,
    '#collapsed'   => TRUE,
    '#title'       => t('Help and instructions'),
  );

  $form['help']['help'] = array(
    '#type'  => 'markup',
    '#value' => revenue_sharing_basic_help_text(),
  );

  $form['required'] = array(
    '#type'        => 'fieldset',
    '#collapsible' => TRUE,
    '#collapsed'   => FALSE,
    '#title'       => t('Required parameters'),
  );

  $form['required']['revenue_sharing_basic_client_id_profile_field'] = array(
    '#type'          => 'select',
    '#title'         => t('Google AdSense client ID profile field'),
    '#default_value' => variable_get('revenue_sharing_basic_client_id_profile_field', REVENUE_SHARING_BASIC_CLIENT_ID_PROFILE_FIELD_DEFAULT),
    '#options'       => revenue_sharing_basic_get_profile_fields(),
    '#required'      => TRUE,
    '#description'   => t('This is the profile field that holds the AdSense Client ID for the site owner as well as (optionally) for site users who participate in revenue sharing. You must enabled the profile module and create a new field for this.'),
  );

  $form['percentage'] = array(
    '#type'        => 'fieldset',
    '#collapsible' => TRUE,
    '#collapsed'   => FALSE,
    '#title'       => t('Revenue sharing percentage'),
  );

  $options = drupal_map_assoc(range(0, 100, 5));

  $form['percentage']['revenue_sharing_basic_percentage_author'] = array(
    '#type'          => 'select',
    '#title'         => t('Percentage of node views going to author'),
    '#default_value' => variable_get('revenue_sharing_basic_percentage_author', REVENUE_SHARING_BASIC_PERCENTAGE_AUTHOR_DEFAULT),
    '#options'       => $options,
  );

  $form['percentage']['role'] = array(
    '#type'        => 'fieldset',
    '#title'       => t('Percentage of node views going to author with the following roles'),
    '#description' => t('When the author belongs to one or more roles, the percentage of node views using his AdSense Client ID will be the maximum between the author value and the following settings for each role.'),
    '#theme'       => 'revenue_sharing_basic_author_percentage_role',
  );

  $roles = user_roles(TRUE);
  unset($roles[array_search('authenticated user', $roles)]);
  foreach ($roles as $role => $role_desc) {
    $form['percentage']['role']['revenue_sharing_basic_percentage_role_'. $role] = array(
      '#type'          => 'select',
      '#title'         => t($role_desc),
      '#default_value' => variable_get('revenue_sharing_basic_percentage_role_'. $role, REVENUE_SHARING_BASIC_PERCENTAGE_ROLE_DEFAULT),
      '#options'       => $options,
    );
  }

  if (module_exists('referral')) {
    $form['percentage']['revenue_sharing_basic_percentage_refer'] = array(
      '#type'          => 'select',
      '#title'         => t('Percentage of node views going to user who referred the author'),
      '#default_value' => variable_get('revenue_sharing_basic_percentage_refer', REVENUE_SHARING_BASIC_PERCENTAGE_REFER_DEFAULT),
      '#options'       => $options,
    );
  }

  $form['content_types'] = array(
    '#type'        => 'fieldset',
    '#collapsible' => TRUE,
    '#collapsed'   => FALSE,
    '#title'       => t('Content types'),
  );

  $types = node_get_types();
  foreach ($types as $type => $name) {
    $form['content_types']['revenue_sharing_basic_node_type_'. $type] = array(
      '#type'          => 'checkbox',
      '#title'         => $name->name,
      '#default_value' => variable_get('revenue_sharing_basic_node_type_'. $type, REVENUE_SHARING_BASIC_NODE_TYPE_DEFAULT),
    );
  }

  $form['#redirect'] = 'admin/settings/adsense/publisher';

  return system_settings_form($form);
}

/**
 * Theme the author percentage part of the settings page.
 *
 * @ingroup themeable
 */
function theme_revenue_sharing_basic_author_percentage_role($form) {
  $output = '';
  $elements = element_children($form);
  if (!empty($elements)) {
    $header = array(t('Role'), t('Percentage'));
    foreach ($elements as $key) {
      $row = array();
      $row[] = $form[$key]['#title'];
      unset($form[$key]['#title']);
      $row[] = drupal_render($form[$key]);
      $rows[] = $row;
    }
    $output .= theme('table', $header, $rows);
  }

  $output .= drupal_render($form);
  return $output;
}

/**
 * Auxiliary function to create the list for the revenue_sharing_basic_client_id_profile_field field
 *
 * @return
 *   array of fields with the field IDs as keys and the field titles as values
 *
 * @ingroup forms
 */
function revenue_sharing_basic_get_profile_fields() {
  $profile_list = array(0 => 'None');

  $result = db_query("SELECT fid, title FROM {profile_fields} ORDER BY fid");
  while ($row = db_fetch_object($result)) {
    $profile_list[$row->fid] = $row->title;
  }

  return $profile_list;
}
