<?php

$filter = new Twig_SimpleFilter('content_image', function($string, $is_pl = false) {
  return $is_pl ? "https://dl.dropboxusercontent.com/s/{$string}" : $string;
});
