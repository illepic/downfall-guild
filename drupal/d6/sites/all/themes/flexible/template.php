<?php

function flexible_regions() {
	return array(
		pre_header => t('pre header'),
		header => t('header'),
		left => t('left sidebar'),
		content=>t('content'),
		right => t('right sidebar'),
		footer => t('footer'),
	);
}

function phptemplate_search_block_form($form) {
	global $search_block;
	$search_block = true;
  return _phptemplate_callback('search-block-form', array('form' => $form));
}

// scan a directory for stylesheets
function scan_stylesheets($themepath, &$stylesheets) {
	if (!file_exists($themepath)) { return; }
	$dir = "$themepath";
	$dh  = opendir($dir);
	while (false !== ($filename = readdir($dh))) {
		$files[] = $filename;
	}
	$font = array();
	$colour = array();
	foreach ($files as $file) {
		if (substr($file,-4) == '.css') {
			$fileargs = explode('.', $file);
			if (count($fileargs) == 3) {
				$stylesheets[$fileargs[0]][$fileargs[1]] = $themepath.'/'.$file;
			}
		}
	}
}
