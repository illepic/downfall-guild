<?php
// $Id: signup_event_5.x-2.inc,v 1.3 2007/12/26 17:34:04 dww Exp $

/**
 * @return Array of SQL clauses for cron reminder email query builder.
 */
function signup_reminder_sql() {
  global $db_type;
  event_include_files();
  switch ($db_type) {
    case 'mysql':
    case 'mysqli':
      $where = array("('". date('Y-m-d H:i:s') ."' + INTERVAL s.reminder_days_before DAY ) > ". event_where_utc());
      break;
    case 'pgsql':
      $where = array("('". date('Y-m-d H:i:s') ."' + INTERVAL 's.reminder_days_before days' ) > ". event_where_utc());
  }
  return array(
    'fields' => array(event_select(), 'e.timezone'),
    'joins' => array(event_join()),
    'where' => $where,
  );
}

/**
 * @return Array of SQL clauses for cron auto-close query builder.
 */
function signup_autoclose_sql() {
  event_include_files();
  return array(
    'fields' => array(event_select(), 'e.timezone'),
    'joins' => array(event_join('s')),
    'where' => array(event_where_utc() ." < '". date('Y-m-d H:i:s', time() + variable_get('signup_close_early', 1) * 3600) ."'"),
  );
}

/**
 * @return Array of SQL clauses for admin overview page query builder.
 */
function signup_admin_sql() {
  return array(
    'fields' => array(event_select(), 'e.timezone'),
    'group_by' => array('event_start', 'e.timezone'),
    'joins' => array(event_join('n', 'LEFT')),
  );
}

function signup_admin_form_header() {
  return array('data' => t('Start'), 'field' => event_select());
}

function signup_admin_form_extra($signup_event) {
  return array(
    '#type' => 'markup',
    '#value' => event_format_date(event_explode_date($signup_event->event['start']), 'custom', variable_get('signup_date_string', 'D, M jS, g:i A')),
  );
}

function signup_list_user_signups_sql() {
  return 'SELECT n.nid, n.title, '. event_select() .' FROM {node} n INNER JOIN {signup_log} s_l ON n.nid = s_l.nid '. event_join('n', 'LEFT') .' WHERE s_l.uid = %d AND ('. event_where() ." >= '". event_implode_date(_event_user_time()) ."' OR e.event_start IS NULL) ORDER BY event_start";
}

/**
 * Returns true if the given node is event-enabled, and the start time
 * has already passed the "Close x hours before" setting.
 */
function _signup_event_completed($node) {
  if (is_numeric($node)) {
    $node = node_load($node);
  }
  if (isset($node->event)) {
    $closing_time = date('Y-m-d H:i:s', time() + (variable_get('signup_close_early', 1) * 3600));
    if (event_is_later($closing_time, $node->event['start_utc'], 'string')) {
      return TRUE;
    }
  }
  return FALSE;
}

function signup_extra_tokens() {
  return array('%time');
}

function signup_format_date($node) {
  return $node->event['start'] ? event_format_date(event_explode_date($node->event['start']), 'custom', variable_get('signup_date_string', 'D, M jS, g:i A')) : t('[Untimed]');
}