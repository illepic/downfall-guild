<?php
// $Id: 
/**
 * @file plugins/relationships/og.inc
 *
 * Plugin to provide an relationship handler for nodes posted to a group.
 */
function og_panels_og_ctools_relationships() {
  $args['og'] = array(
    'title' => t('Organic Group from node'),
    'keyword' => 'og',
    'description' => t('Adds a group from a node context; if multiple groups are associated with a node, this will get the "first" group only.'),
    'required context' => new ctools_context_required(t('Node'), 'node'),
    'context' => 'og_panels_group_from_node_context',
  );
  return $args;
}

/**
 * Return a new context based on an existing context
 */
function og_panels_group_from_node_context($context = NULL, $conf) {
  // If unset it wants a generic, unfilled context, which is just NULL
  if (empty($context->data)) {
    return ctools_context_create_empty('og');
  }
  
  if (isset($context->data->type) && og_is_group_type($context->data->type)) {
    return ctools_context_create('og', $context->data);
  }

  if ($group = og_get_group_context()) {
    return ctools_context_create('og', $group);
  }
}