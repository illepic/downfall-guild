<?php
// $Id$

/**
 * @file
 * Administration page callbacks for FuriousRaid Points module
 */

/**
 * Form builder. Configure frpoints
 *
 * @ingroup forms
 * @see system_settings_form()
 */
function frpoints_admin_settings() {
	$form['frpoints_named_raids'] = array(
		'#title' => t('Individual Raids'),
		'#type' => 'textarea',
		'#description' => t('Please list the names of your raids, one per line'),
		'#default_value' => variable_get('frpoints_named_raids', array()),
		'#cols' => 40,
		'#rows' => 3,
		'#resizable' => FALSE,
		'#weight' => 15,
	);
	return system_settings_form($form);
}
