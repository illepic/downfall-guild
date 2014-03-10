<?php
// $Id: wowarmory.inc,v 1.3.2.2 2010/03/24 00:51:18 nhdriver4 Exp $

/**
 * @file
 * Functions for the wowarmory module.
 */

/**
 * This function connects to the The World of Warcraft Armory and downloads the
 * requested data
 *
 * @return
 *  XML source code from the wow armory
 */
function _wowarmory_curl_guild() {

  // Pretend to be Firefox.
  $useragent = "User-Agent: Mozilla/5.0 (Windows; U; Windows NT 5.1; en-US; rv:1.8.1.2) Gecko/20070219 Firefox/2.0.0.2";

  /**
	 * Need some error checking here.... compare page against an array of valid page names?
	 */
  // Create the uri that curl will load, dependant on the region that the guild resides in
  if (variable_get('wowarmory_region', 'en') == 0) {
    $xml_url = "http://www.wowarmory.com/guild-info.xml?r=" . urlencode(variable_get('wowarmory_realm', '')) . "&gn=" . urlencode(variable_get('wowarmory_guild', ''));
  }
  if (variable_get('wowarmory_region', 'en') == 1) {
    $xml_url = "http://eu.wowarmory.com/guild-info.xml?r=" . urlencode(variable_get('wowarmory_realm', '')) . "&gn=" . urlencode(variable_get('wowarmory_guild', ''));
  }

  //echo "Downloading XML From: " . $xml_url . "<br/ >";

  // Run with it
  $ch = curl_init();
  curl_setopt($ch, CURLOPT_URL, $xml_url);
  curl_setopt($ch, CURLOPT_HEADER, 0);
  curl_setopt($ch, CURLOPT_RETURNTRANSFER, 1);
  curl_setopt($ch, CURLOPT_USERAGENT, $useragent);
  //curl_setopt($ch, CURLOPT_FOLLOWLOCATION, TRUE);
  $data = curl_exec($ch);
  curl_close($ch);

  // New attempt at detecting maintenance mode. Working as of 3/23/2010
  if (strpos($data, "maintenance") == TRUE) {
    watchdog('wowarmory', 'Armory is in maintenance mode. No changes made.', array(), WATCHDOG_NOTICE);
    exit();
  }
  if (strpos($data, "404") == TRUE) {
    watchdog('wowarmory', 'Armory returned a 404 error. No changes made.', array(), WATCHDOG_NOTICE);
    exit();
  }
  else {
    echo 'returning data.';
    return $data;
  }
}

/**
 * Connect to the armory and return the chracter XML
 *
 * @param string $cn
 *  The character name to parse
 * @return unknown
 */
function _wowarmory_curl_toon($cn) {
  // Pretend to be Firefox.
  $useragent = "User-Agent: Mozilla/5.0 (Windows; U; Windows NT 5.1; en-US; rv:1.8.1.2) Gecko/20070219 Firefox/2.0.0.2";

  /**
	 * Need some error checking here.... compare page against an array of valid page names?
	 */
  // Create the uri that curl will load, dependant on the region that the guild resides in
  if (variable_get('wowarmory_region', 'en') == 0) {
    $xml_url = "http://www.wowarmory.com/character-sheet.xml?r=" . urlencode(variable_get('wowarmory_realm', '')) . "&cn=". urlencode($cn) ."&gn=" . urlencode(variable_get('wowarmory_guild', ''));
  }
  if (variable_get('wowarmory_region', 'en') == 1) {
    $xml_url = "http://eu.wowarmory.com/character-sheet.xml?r=" . urlencode(variable_get('wowarmory_realm', '')) . "&cn=". urlencode($cn) ."&gn=" . urlencode(variable_get('wowarmory_guild', ''));
  }

  //echo $xml_url;

  // Run with it
  $ch = curl_init();
  curl_setopt($ch, CURLOPT_URL, $xml_url);
  curl_setopt($ch, CURLOPT_HEADER, 0);
  curl_setopt($ch, CURLOPT_RETURNTRANSFER, 1);
  curl_setopt($ch, CURLOPT_USERAGENT, $useragent);
  $data = curl_exec($ch);
  curl_close($ch);

  return $data;
}

function _wowarmory_update_toon($name) {
  $xmldoc = new DOMDocument();
  $xmldoc->loadXML(_wowarmory_curl_toon($name));
  echo '<pre>';

  // Talents
  $talents = $xmldoc->getElementsByTagName("talentSpec");
  foreach ($talents as $talent) {
    $data['talents'][] = array(
    'active' => $talent->getAttribute("active"),
    'group' => $talent->getAttribute("group"),
    'icon' => $talent->getAttribute("icon"),
    'prim' => $talent->getAttribute("prim"),
    'treeOne' => $talent->getAttribute("treeOne"),
    'treeTwo' => $talent->getAttribute("treeTwo"),
    'treeThree' => $talent->getAttribute("treeThree"),
    );
    //print_r($data);
  }

  // Professions
  $professions = $xmldoc->getElementsByTagName("skill");
  foreach ($professions as $profession) {
    $data['profession'][] = array(
    'id' => $profession->getAttribute("id"),
    'key' => $profession->getAttribute("key"),
    'max' => $profession->getAttribute("max"),
    'name' => $profession->getAttribute("name"),
    'value' => $profession->getAttribute("value"),
    );

  }
  print_r($data);



  //echo $charactersheet;
  echo '</pre>';
}

/**
 * Updates the roster adding new, updating existing, and removing missing characters
 *
 */
function _wowarmory_update_roster() {

  $doc = new DOMDocument();
  $xml_str = _wowarmory_curl_guild();
  //echo $xml_str;
  $doc->loadXML($xml_str);
  $member_list = $doc->getElementsByTagName("character");

  /**
	 * This whole process needs to to updated to use only one query for the
	 * entire guild insertion, instead of one for each member
	 * Also fix the overall process to cut down on the total queries
  */
  $query = "SELECT name FROM {wowarmory_roster}";
  $result = db_query($query);
  $current = array();
  while ($row = db_fetch_array($result)) {
    $current[] = $row['name'];
  }

  foreach ($member_list as $toon) {
    $data = array(
      'achPoints' => $toon->getAttribute("achPoints"),
      'classId' => $toon->getAttribute("classId"),
      'genderId'  => $toon->getAttribute("genderId"),
      'level'  => $toon->getAttribute("level"),
      'name'  => $toon->getAttribute("name"),
      'raceId'  => $toon->getAttribute("raceId"),
      'rank'  => $toon->getAttribute("rank"),
    );
    //echo '<pre>';
    //print_r($data);


    // Does the character already exist?
    // We can check this from the query that we already ran. member names are listed in the
    $query = "SELECT id FROM {wowarmory_roster} WHERE name = '" . $data['name'] . "';";

    // the character exists, update
    if ($id = db_result(db_query($query))) {
      $sql_update = "UPDATE {wowarmory_roster} SET level = " . $data['level'] . ", achPoints = ". $data['achPoints'] . " WHERE ID = '" . $id . "';";
      db_query($sql_update);

    }
    else {
      // the character is new, insert
      $sql_insert = "INSERT INTO {wowarmory_roster} ( achPoints, classId, genderId, level, name, raceId, rank ) " .
      "VALUES ('" . $data['achPoints'] . "', '" . $data['classId'] . "', '" . $data['genderId'] . "', '" . $data['level'] . "', '" . $data['name'] . "', '" . $data['raceId'] . "', '" . $data['rank'] . "')";
      db_query($sql_insert);
      watchdog('wowarmory', $data['name'] . ' has been added to the roster.' , array(), WATCHDOG_NOTICE);
    }

    // As we filter through each player from wowarmory.com, remove them from our tracking array.
    foreach ($current as $key => $value) {
      if ($value == $data['name']) {
        unset($current[$key]);
      }
    }

    // Update the index's for the array (This may not be required, but lets keep it clean.
    $current = array_values($current);

  }

  // Clean up the players that were not seen on the roster page.
  //echo '<br />The following players were not seen, and are being removed: ';
  foreach ($current as $name) {
    watchdog('wowarmory', $name . " has been removed from the roster.");
    db_query("DELETE FROM {wowarmory_roster} WHERE name = '%s'", $name);
  }

  watchdog('wowarmory', 'Armory updated successfully.', array(), WATCHDOG_NOTICE);
}