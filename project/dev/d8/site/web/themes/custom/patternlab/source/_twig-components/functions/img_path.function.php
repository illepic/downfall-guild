<?php

$function = new Twig_SimpleFunction('img_path', function ($string, $pl = false) {

  if ($pl) {
    $dropbox = 'https://dl.dropboxusercontent.com/s';
    return "{$dropbox}/{$string}";
  } else {
    return $string;
  }
});
