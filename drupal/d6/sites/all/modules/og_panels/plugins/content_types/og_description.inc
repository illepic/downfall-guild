<?php
// $Id;

/**
 * Callback function to supply a list of content types.
 */
function og_panels_og_description_ctools_content_types() {
  return array(
    'single' => TRUE,
    'title' => t('OG description'),
    'icon' => 'user-multiple.png',
    'admin_title' => t('The organic group description'),
    'required context' => new ctools_context_required(t('Organic Group'), 'og'),
    'category' => 'Organic groups',
  );
}

/**
 * Render the description
 */
function og_panels_og_description_content_type_render($subtype, $conf, $panel_args, $context) {
  if (empty($context) || empty($context->data)) {
    return;
  }

  // Get a shortcut to the node.
  $group = $context->data;

  // Build the content type block.
  $block = new stdClass();
  $block->module  = 'og_description';
  $block->title   = $type->title_label;
  $block->content = check_markup($group->og_description);
  $block->delta   = $node->nid;

  return $block;
}

/**
 * Edit form for the description content type.
 */
function og_panels_og_description_content_type_edit_form(&$form, &$form_state) {
  // Empty form to ensure we have the override title + context gadgets.
}


/**
 * Returns the administrative title for a type.
 */
function og_panels_og_description_content_type_admin_title($subtype, $conf, $context) {
  return t('Description');
}
