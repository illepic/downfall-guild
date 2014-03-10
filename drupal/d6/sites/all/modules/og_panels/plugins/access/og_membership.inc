<?php
// $Id: og_membership.inc,v 1.1.2.1 2010/03/30 02:31:39 populist Exp $

/**
 * @file
 * Access plugin that checks OG membership status of the logged in user.
 */

/**
 * Plugins are described by creating a $plugin array which will be used
 * by the system that includes this file.
 */
$plugin = array(
  'title' => t("User: OG membership"),
  'description' => t('Check current user membership status.'),
  'callback' => 'og_membership_ctools_access_check',
  'default' => array('type' => 'view'),
  'settings form' => 'og_membership_ctools_access_settings',
  'summary' => 'og_membership_ctools_access_summary',
  'required context' => array(
    new ctools_context_required(t('Group'), 'og'),
  ),
);

/**
 * Check access.
 */
function og_membership_ctools_access_check($conf, $context) {
  list($node_context) = $context;
  if (empty($node_context) || empty($node_context->data) || empty($node_context->data->type)) {
    return FALSE;
  }
  $group = &$node_context->data;

  list($txt, $subscription) = og_subscriber_count_link($group);
  if ($subscription === $conf['membership']) {
    return TRUE;
  }
  return FALSE;
}

/*
 * Settings form.
 */
function og_membership_ctools_access_settings(&$form, &$form_state, $conf) {
  $form['settings']['membership'] = array(
    '#title' => t('Membership status'),
    '#type'  => 'radios',
    '#options' => _og_membership_options(),
    '#description' => t('Select membership status to compare with.'),
    '#default_value' => $conf['membership'],
  );
}

function _og_membership_options() {
  return array(
    '' => t('Not member'),
    'active'     => t('Member'),
    'requested'  => t('Membership awaits approval'),
  );
}

/**
 * Provide a summary description based upon the checked group.
 */
function og_membership_ctools_access_summary($conf, $context) {
  list($group_context) = $context;
  $options = _og_membership_options();
  $replace = array('@status' => $options[$conf['membership']], '@group' => $group_context->identifier);
  return t('Current user has "@status" membership status in "@group" group.', $replace);
}
