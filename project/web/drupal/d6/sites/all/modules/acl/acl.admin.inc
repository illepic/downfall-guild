<?php

/**
 * @file
 * Implementations of administration functions for the acl module.
 */

/**
 * Implementation of acl_edit_form().
 */
function _acl_edit_form($acl_id, $label = NULL, $new_acl = FALSE) {
  $users = array();
  if (!$new_acl) {
    // Ensure the ACL in question even exists.
    if (!$record = db_fetch_array(db_query("SELECT name, number FROM {acl} WHERE acl_id = %d", $acl_id))) {
      return array();
    }
    $result = db_query("SELECT u.uid, u.name FROM {users} u LEFT JOIN {acl_user} aclu ON aclu.uid = u.uid WHERE acl_id = %d", $acl_id);
    while ($user = db_fetch_object($result)) {
      $users[$user->uid] = $user->name;
    }
  }
  if (!isset($label)) {
    $label = (isset($record['name']) ? $record['name'] : (isset($record['number']) ? $record['number'] : $acl_id));
  }

  $form = array(
    '#type' => 'fieldset',
    '#collapsible' => TRUE,
    '#title' => $label,
    '#tree' => TRUE,
  );

  $form['acl_id'] = array('#type' => 'value', '#value' => $acl_id);

  $form['deletions'] = array('#type' => 'checkboxes', '#options' => array()); // placeholder
  $form['delete_button'] = array(
    '#type' => 'button',
    '#name' => 'acl_'. $acl_id,
    '#value' => t('Remove Checked'),
    '#submit' => FALSE,
  );

  $form['add'] = array(
    '#type' => 'textfield',
    '#title' => t('Add user'),
    '#maxlength' => 60,
    '#size' => 40,
    '#autocomplete_path' => 'user/autocomplete',
  );
  $form['add_button'] = array(
    '#type' => 'button',
    '#name' => 'acl_'. $acl_id,
    '#value' => t('Add User'),
    '#submit' => FALSE,
  );

  $form['user_list'] = array(
    '#type' => 'hidden',
    '#default_value' => serialize($users),
  );

  $form['#after_build'] = array('_acl_edit_form_after_build');

  return $form;
}

/**
 * Process a form that had our buttons on it.
 */
function _acl_edit_form_after_build($form, $form_state) {
  // We can't use the form values because it's the entire structure
  // and we have no clue where our values actually are. That's
  // ok tho cause #value still works for us.
  $user_list = unserialize($form['user_list']['#value']);
  $button_name = 'acl_'. $form['acl_id']['#value'];

  if (isset($form['#post'][$button_name]) && $form['#post'][$button_name] == $form['delete_button']['#value']) {
    $deletions = $form['deletions']['#value'];
    foreach ($deletions as $uid) {
      unset($user_list[$uid]);
      unset($form['deletions']['#value'][$uid]);
    }
  }
  elseif (isset($form['#post'][$button_name]) && $form['#post'][$button_name] == $form['add_button']['#value']) {

    $user = db_fetch_object(db_query("SELECT uid, name FROM {users} WHERE name = '%s'", $form['add']['#value']));
    if (!$user || !$user->uid) {
      form_error($form['add'], t("Invalid user specified."));
    }
    else {
      $user_list[$user->uid] = $user->name;
      $form['add']['#value'] = NULL;
    }
  }

  if (count($user_list) != 0) {
    $form['deletions']['#type'] = 'checkboxes';
    $form['deletions']['#title'] = t("Current users");
    $form['deletions']['#options'] = $user_list;
    $form['deletions']['#value'] = array(); // don't carry value through.
    $form['deletions'] = form_builder(!empty($form['#post']) ? $form['#post']['form_id'] : 'acl_form', $form['deletions'], $form_state);
  }
  else {
    $form['delete_button']['#type'] = 'value';
  }
  $form['user_list']['#value'] = serialize($user_list);

  return $form;
}

/**
 * Write the results of a form.
 *
 * The module that embedded our form must call this function!
 */
function acl_save_form($form, $priority = NULL) {
  $users = unserialize($form['user_list']);
  db_query('DELETE FROM {acl_user} WHERE acl_id = %d', $form['acl_id']);
  foreach ($users as $uid => $name) {
    db_query('INSERT INTO {acl_user} (acl_id, uid) VALUES (%d, %d)', $form['acl_id'], $uid);
  }
  if (isset($priority)) {
    db_query('UPDATE {acl_node} SET priority = %d where acl_id = %d', $priority, $form['acl_id']);
  }
}

