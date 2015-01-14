<?php

/**
 * @file
 * Contains the functions to display the logs tracked by the adsense_click
 * module.
 *
 * This file is included by the adsense_click module.
 */

function adsense_click_log() {
  $header = array(
    array('data' => t('Timestamp'), 'field' => 'timestamp', 'sort' => 'desc'),
    array('data' => t('Path'),      'field' => 'path'),
    array('data' => t('IP/Host'),   'field' => 'ip'),
    array('data' => t('Referrer'),  'field' => 'referrer'),
  );

  $name_resolve = variable_get('adsense_click_tracking_name_resolve', ADSENSE_CLICK_TRACKING_NAME_RESOLVE_DEFAULT);

  $sql = 'SELECT * FROM {adsense_clicks} '. tablesort_sql($header);

  $result = pager_query($sql, 50);
  while ($log = db_fetch_object($result)) {
    if ($name_resolve) {
      $host = gethostbyaddr($log->ip);
    }
    else {
      $host = $log->ip;
    }

    $rows[] = array(
      array('data' => format_date($log->timestamp, 'small'), 'nowrap' => 'nowrap'),
      _adsense_click_format_path($log->path, $log->title),
      l($host, 'http://whois.domaintools.com/'. $log->ip),
      _adsense_click_format_path($log->referrer),
    );
  }

  return theme('table', $header, $rows) . theme('pager', NULL, 50, 0);
}

function adsense_click_top_pages() {
  $header = array(
    array('data' => t('Path'),   'field' => 'path'),
    array('data' => t('Clicks'), 'field' => 'count', 'sort' => 'desc'),
    array('data' => t('Last'),   'field' => 'last'),
  );

  $sql = 'SELECT path, COUNT(*) AS count, MAX(timestamp) AS last FROM {adsense_clicks} GROUP BY path'. tablesort_sql($header);

  $result = pager_query($sql, 50);
  while ($log = db_fetch_object($result)) {
    $title = db_result(db_query("SELECT title FROM {adsense_clicks} WHERE path = '%s'", $path));
    $rows[] = array(
      array('data' => _adsense_click_format_path($log->path, $title)),
      array('data' => $log->count, 'align' => 'right'),
      array('data' => format_date($log->last, 'small'), 'nowrap' => 'nowrap'),
    );
  }

  return theme('table', $header, $rows) . theme('pager', NULL, 50, 0);
}

function adsense_click_by_day() {
  global $db_type;
  $header = array(
    array('data' => t('Day'),    'field' => 'day', 'sort' => 'desc'),
    array('data' => t('Clicks'), 'field' => 'count'),
  );

  switch ($db_type) {
    case 'mysql':
    case 'mysqli':
      $sql_count = "SELECT COUNT(DISTINCT(FROM_UNIXTIME(timestamp, '%y-%m-%%d'))) FROM {adsense_clicks}";
      $sql = "SELECT FROM_UNIXTIME(timestamp, '%Y-%m-%%d') AS day, COUNT(*) AS count FROM {adsense_clicks} GROUP BY day" . tablesort_sql($header);
      break;
    case 'pgsql':
      $sql_count = "SELECT COUNT(DISTINCT(TO_CHAR(timestamp, 'YYYY-MM-DD'))) FROM {adsense_clicks}";
      $sql = "SELECT TO_CHAR(timestamp, 'YYYY-MM-DD') AS day, COUNT(*) AS count FROM {adsense_clicks} GROUP BY day" . tablesort_sql($header);
      break;
  }

  $result = pager_query($sql, 50, 0, $sql_count);
  while ($log = db_fetch_object($result)) {
    $rows[] = array(
      $log->day,
      array('data' => $log->count, 'align' => 'right'),
    );
  }

  return theme('table', $header, $rows) . theme('pager', NULL, 50, 0);
}

function _adsense_click_format_path($path, $title = '', $width = 32) {
  global $base_url;

  if ($title) {
    $short_title = truncate_utf8($title, $width, FALSE, TRUE);
  }
  else {
    $title = $path;
    $short_path = preg_replace('?^'. $base_url .'?', '', $path);
    $short_title = truncate_utf8($short_path, $width, FALSE, TRUE);
  }

  return l($short_title, $path, array('attributes' => array('title' => $title)));
}
