<?php

// $Id: wowdb.inc,v 1.1.2.2 2009/05/22 20:25:29 professorbikeybike Exp $

/**
 * @file
 *   Provide WOW Lootz hooks for the Wowdb.com (http://www.wowdb.com) WOW database
 */

define('WOWDB_BASE_URL', 'http://www.wowdb.com');
define('WOWDB_SEARCH_NAME', 'search.aspx?search_text=');
define('WOWDB_SEARCH_ID', 'item.aspx?id=');

/**
 * Implementation of lootz_hook_item_db_info()
 */
function lootz_wowdb_item_db_info() {
  return array('wowdb' => t('<a href="!url">WoW DB</a>'));
}

/**
 * Implementation of lootz_hook_filter_description()
 */
function lootz_wowdb_filter_description() {
  return t('Converts [item] tags to links/tooltips of the configured item database (<a href="!url">WoW DB</a> is the default).', array('!url' => WOWDB_BASE_URL));
}

/**
 * Implementation of lootz_hook_filter_tips()
 */
function lootz_wowdb_filter_tips() {
  return t('You can include [item][/item] tags to automatically link the items to <a href="!url">Wow DB</a>. Either use the <em>Item ID</em> ([item]1234[/item]) or the <em>exact name</em> ([item]Earthwarden[/item])', array('!url' => WOWDB_BASE_URL));
}

/**
 * Implementation of lootz_hook_id_lookup()
 */
function lootz_wowdb_id_lookup($name) {
  $url = WOWDB_BASE_URL . '/' . WOWDB_SEARCH_NAME . drupal_urlencode($name);
  $page = drupal_http_request($url);
  if ($page->code == '200') {
    // find id via this redirect tag: <script>self.location="item.aspx?id=29171";</script>
    if (preg_match('/self\.location="'. preg_quote(WOWDB_SEARCH_ID) . '([0-9]+)";/', $page->data, $m)) {
      return check_plain($m[1]);
    }
  }
  return false;
}

/**
 * Implementation of lootz_hook_name_lookup()
 */
function lootz_wowdb_name_lookup($id) {
  // grab search results
  $page = drupal_http_request(WOWDB_BASE_URL . '/' . WOWDB_SEARCH_ID . $id);
  if ($page->code == '200') {
    // search for title tag of the form:
    // <h1 id="ctl00_MainContent_PageHeader" title="World of Warcraft Halberd of Desolation">Halberd of Desolation</h1>
    if (preg_match('/<h1 id="ctl00_MainContent_PageHeader" title=".*">(.*)<\/h1>/i', $page->data, $m)) {
      return check_plain($m[1]);
    }
  }
  return $id;
}

/**
 * Implementation of lootz_hook_quality_lookup()
 */
function lootz_wowdb_quality_lookup($id, $name) {
  // pattern: <b class=r4>Earthwarden</b>
  $page = drupal_http_request(WOWDB_BASE_URL . '/' . WOWDB_SEARCH_ID . $id);
  if ($page->code == '200') {
    if (preg_match('/<b class="?(r[0-9]{1})"?>/', $page->data, $m)) {
      switch ($m[1]) {
      case 'r1' :
	// r3: common
	$quality = 'common';
	break;
      case 'r2' :
	// r3: uncommon
	$quality = 'uncommon';
	break;
      case 'r3' :
	// r3: rare
	$quality = 'rare';
	break;
      case 'r4' :
	// r4: epic
	$quality = 'epic';
	break;
      case 'r5' :
	// r5: legendary
	$quality = 'legendary';
	break;
      case 'r6' :
	// r6: artifact?
	$quality = 'artifact';
	break;
      default:
	$quality = false;
      }
    }
  }
  return $quality;
}

/**
 * Implementation of lootz_hook_link_item()
 */
function lootz_wowdb_link_item($name, $id) {
  $url = WOWDB_BASE_URL . '/' . WOWDB_SEARCH_ID . $id;
  return theme('lootz_link_item', $url, $name, $id);
}

/**
 * Implementation of lootz_hook_init()
 */
function lootz_wowdb_init() {
  // include the external js
  drupal_set_html_head('<script src="http://www.wowdb.com/js/extooltips.js?8" type="text/javascript" ></script>'."\n");
}
