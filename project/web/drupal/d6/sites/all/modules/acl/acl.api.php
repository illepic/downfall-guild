<?php

/**
 * @file
 * API documentation for ACL.
 */

/**
 * Explain what your ACL grant records mean.
 */
function hook_acl_explain($acl_id, $name, $users = NULL) {
  if (empty($users)) {
    return "ACL (id=$acl_id) would grant access to $name.";
  }
  return "ACL (id=$acl_id) grants access to $name to the listed user(s).";
}

