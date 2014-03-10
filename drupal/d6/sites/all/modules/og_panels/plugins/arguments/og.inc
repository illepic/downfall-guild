<?php
// $Id:

/**
 * @file
 *
 * Plugin to provide an argument handler for an OG node id
 */

/**
 * Implementation of specially named hook_ctools_arguments().
 */
function og_panels_og_ctools_arguments() {
  $args['og'] = array(
    'title' => t("Organic Group"),
    'keyword' => 'og',
    'description' => t('Creates a node context from a group ID argument.'),
    'context' => 'og_panels_og_context',
    'placeholder form' => array(
      '#type' => 'textfield',
      '#description' => t('Enter the node ID of a group for this argument'),
    ),
  );
  return $args;
}

/**
 * Discover if this argument gives us the node we crave.
 */
function og_panels_og_context($arg = NULL, $conf = NULL, $empty = FALSE) {
  // If unset it wants a generic, unfilled context.
  if ($empty) {
    return ctools_context_create_empty('og');
  }

  // We can accept either a node object or a pure nid.
  if (is_object($arg)) {
    return ctools_context_create('og', $arg);
  }

  if (!is_numeric($arg)) {
    return FALSE;
  }

  $node = node_load($arg);
  if (!$node->og_mission) {
    return FALSE;
  }

  return ctools_context_create('og', $node);
}

