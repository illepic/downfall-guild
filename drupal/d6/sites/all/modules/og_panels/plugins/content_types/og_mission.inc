<?php
// $Id;

/**
 * Callback function to supply a list of content types.
 */
function og_panels_og_mission_ctools_content_types() {
  return array(
    'single' => TRUE,
    'title' => t('OG Mission'),
    'icon' => 'user-multiple.png',
    'admin_title' => t('The organic group mission/welcome message'),
    'required context' => new ctools_context_required(t('Organic Group'), 'og'),
    'category' => 'Organic groups',
  );
}

function og_panels_og_mission_content_type_render($subtype, $conf, $panel_args, $context) {
  $node = isset($context->data) ? drupal_clone($context->data) : NULL;
  $block->module = 'og_mission';

  $block->title = t('Welcome');
  if ($node) {
    // This rendering somewhat verbose technique exactly matches og_view_group().
    $value = check_markup($node->body, $node->format, FALSE);
    $form['og_mission'] = array(
      '#theme' => 'og_mission', 
      '#value' => $value,
      '#node' => $node,
      '#weight' => -3,
    );
    $block->content = drupal_render($form['og_mission']);
    
    $block->delta = $node->nid;
  }
  else {
    $block->content = t('Welcome statement goes here.');
    $block->delta = 'unknown';
  }

  return $block;
}
/**
 * Edit form for the mission content type.
 */
function og_panels_og_mission_content_type_edit_form(&$form, &$form_state) {
  // Empty form to ensure we have the override title + context gadgets.
}


/**
 * Returns the administrative title for a type.
 */
function og_panels_og_mission_content_type_admin_title($subtype, $conf, $context) {
  return t('Mission');
}
