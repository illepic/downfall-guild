<?php

/**
 * @file
 * Theme functions for Image assist.
 */


/**
 * Setup variables for the browser thumbnail template.
 * 
 * @param array $vars
 */
function template_preprocess_img_assist_browser_thumbnail(&$vars) {
  $node = node_load($vars['row']->nid);

  $vars['thumbnail'] = img_assist_display($node, IMAGE_THUMBNAIL);
  $vars['path'] = url('img_assist/properties/'. $node->nid); 
  $vars['title'] = $node->title; 
}

