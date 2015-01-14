<?php
// $Id: signup_no_views.inc,v 1.4 2008/01/26 03:02:39 dww Exp $

/**
 * @file
 * Provides all the code for required UI elements for sites that do
 * not have views.module enabled. If views is enabled, there are
 * default views for all of these things (which are therefore
 * customizable and more powerful) in signup_views.inc.
 *
 */

/**
 * Implementation of hook_block().
 * @ingroup signup_core
 * @param $op
 *   The operation that is being requested. This defaults to 'list', which
 *   indicates that the method should return which blocks are available.
 * @param $delta
 *   The specific block to display (the offset into an array).
 * @return
 *   One of two possibilities. The first is an array of available blocks.
 *   The other is an array containing a block.
 */
function signup_block($op = 'list', $delta = 0) {
  global $user;
  switch ($op) {
    case 'list' :
      $blocks[0]['info'] = t('Current signups');
      return $blocks;
      break;
    case 'view' :
      if (user_access('access content')) {
        switch ($delta) {
          case 0:
            $titles = signup_list_user_signups($user->uid);
            if (count($titles)) {
              $block['subject'] = t('Current signups');
              $block['content'] = theme_item_list($titles) . l(t('View signup schedule'), "user/$user->uid/signups");
            }
            return $block;
        }
      }
  }
}

/**
 * Implementation of hook_user().
 * @ingroup signup_core
 */
function signup_user($op, &$edit, &$user, $category = NULL) {
  switch ($op) {
    case 'view':
      // grab list of events the user signed up for.
      $signups = signup_list_user_signups($user->uid);
      if (count($signups)) {
        $output = '<h4>'. t('Current signups') .' -- '. l(t('view signup schedule'), "user/$user->uid/signups") .'</h4>'. theme_item_list($signups);
      }
      if (isset($output)) {
        return array(t('Signup information') => array(array('value' => $output, 'class' => 'user')));
      }
  }
}

/**
 * Menu items we only need to define if views is not enabled.
 */
function signup_no_views_menu(&$items) {
  global $user;
    // User signup schedule callback
    $items['user/'. arg(1) .'/signups'] = array(
      'access callback' => ($user->uid == arg(1)) ? TRUE : 'user_access',
      'access arguments' => array('administer all signups'),
      'type' => MENU_CALLBACK,
      'page callback' => 'signup_user_schedule',
      'page arguments' => array('uid' => arg(1)),
    );
}

/**
 * Prints a schedule of the given user's signups.
 * @ingroup signup_callback
 */
function signup_user_schedule($uid) {
  $output = '';
  $user = user_load(array('uid' => $uid));
  if (!$user) {
    drupal_not_found();
    return;
  }
  include_once(drupal_get_path('module', 'signup') .'/signup.theme');
  drupal_set_title(t('Signups for @user', array('@user' => $user->name)));
  $titles = signup_list_user_signups($user->uid);
  foreach ($titles as $nid => $title) {
    $node = node_load(array('nid' => $nid));
    $output .= theme('signup_user_schedule', $node);
  }
  return $output;
}
