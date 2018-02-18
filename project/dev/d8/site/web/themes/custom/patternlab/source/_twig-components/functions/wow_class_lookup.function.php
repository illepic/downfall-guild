<?php

$function = new Twig_SimpleFunction('wow_class_lookup', function($class_id, $classes) {

  $key = array_search($class_id, array_column($classes, 'id'));
  return $classes[$key]['name'];
});
