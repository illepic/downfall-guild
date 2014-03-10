<?php
//template for Marinelli Theme
//author: singalkuppe - www.signalkuppe.com

// regions for meteonetwork 
function marinelli_regions() {
    return array(
        'sidebar_left' => t('sidebar left'),
        'sidebar_right' => t('sidebar right'),
        'content' => t('content'),
    );
}



function marinelli_width($sidebar_left, $sidebar_right) {
  $width = 540;
  if (!$sidebar_left ) {
    $width = $width +190;
  }  
  
   if (!$sidebar_right) {
    $width = $width +190;
  }
  return $width;
}


/**
active trail for menu
*
*/
function phptemplate_menu_item_link($item, $link_item) {
  static $menu;
  if (!isset($menu)) {
    $menu = menu_get_menu();
  }
  $mid = $menu['path index'][$link_item['path']];
  $front = variable_get('site_frontpage','node');
  $attribs = isset($item['description']) ? array('title' => $item['description']) : array();
  $attribs['id'] = 'menu-'. str_replace(' ', '-', strtolower($item['title']));
  if((($link_item['path']=='<front>') && ($front==$_GET['q'])) ||
    (menu_in_active_trail($mid))){
  $attribs['class'] = 'active';
  }
  return l($item['title'], $link_item['path'], $attribs);
}
