<?php

/**
 * @file
 * Contains the administrative functions of the adsense_cse module.
 *
 * This file is included by the adsense_cse module, and includes the
 * settings form.
 */

/**
 * Menu callback for the adsense_cse module settings form.
 *
 * @ingroup forms
 */
function adsense_cse_settings() {
  global $base_url;
  module_load_include('inc', 'adsense_cse', 'help/adsense_cse.help');
  module_load_include('inc', 'adsense', 'includes/adsense.search_options');

  $form['help'] = array(
    '#type'        => 'fieldset',
    '#collapsible' => TRUE,
    '#collapsed'   => TRUE,
    '#title'       => t('Help and instructions'),
  );

  $form['help']['help'] = array(
    '#type'  => 'markup',
    '#value' => adsense_cse_help_text(),
  );

  $form['searchbox'] = array(
    '#type' => 'fieldset',
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
    '#title' => t('Search Box Options'),
  );

  $form['searchbox']['adsense_cse_logo'] = array(
    '#type' => 'radios',
    '#title' => t('Logo Type'),
    '#default_value' => variable_get('adsense_cse_logo', ADSENSE_CSE_LOGO_DEFAULT),
    '#options' => array(
      'adsense_cse_branding_watermark' => t('Watermark on search box (requires JavaScript)'),
      'adsense_cse_branding_right'     => t('Next to the search box'),
      'adsense_cse_branding_bottom'    => t('Below the search box'),
    ),
  );

  $form['searchbox']['adsense_cse_color_box_background'] = array(
    '#type' => 'select',
    '#title' => t('Background color'),
    '#default_value' => variable_get('adsense_cse_color_box_background', ADSENSE_CSE_COLOR_BOX_BACKGROUND_DEFAULT),
    '#options' => array(
      'FFFFFF' => t('White'),
      '999999' => t('Gray'),
      '000000' => t('Black'),
    ),
  );

  $form['searchbox']['adsense_cse_encoding'] = array(
    '#type' => 'select',
    '#title' => t('Site Encoding'),
    '#default_value' => variable_get('adsense_cse_encoding', ADSENSE_CSE_ENCODING_DEFAULT),
    '#options' => _adsense_search_options_encoding(),
  );

  $form['searchbox']['adsense_cse_textbox_length'] = array(
    '#type' => 'textfield',
    '#title' => t('Text Box Length'),
    '#default_value' => variable_get('adsense_cse_textbox_length', ADSENSE_CSE_TEXTBOX_LENGTH_DEFAULT),
    '#size' => 2,
    '#maxlength' => 2,
  );

  $form['searchbox']['adsense_cse_language'] = array(
    '#type' => 'select',
    '#title' => t('Watermark Language'),
    '#default_value' => variable_get('adsense_cse_language', ADSENSE_CSE_LANGUAGE_DEFAULT),
    '#options' => _adsense_search_options_language(),
  );

  $form['result'] = array(
    '#type' => 'fieldset',
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
    '#title' => t('Search Results Style'),
  );

  $form['result']['adsense_cse_country'] = array(
    '#type' => 'select',
    '#title' => t('Country or territory for Google domain'),
    '#default_value' => variable_get('adsense_cse_country', ADSENSE_CSE_COUNTRY_DEFAULT),
    '#options' => _adsense_search_options_country(),
  );

  $form['result']['adsense_cse_frame_width'] = array(
    '#type' => 'textfield',
    '#title' => t('Width of results area'),
    '#default_value' => variable_get('adsense_cse_frame_width', ADSENSE_CSE_FRAME_WIDTH_DEFAULT),
    '#size' => 3,
    '#maxlength' => 4,
  );

  $form['result']['adsense_cse_ad_location'] = array(
    '#type' => 'radios',
    '#title' => t('Ad Location'),
    '#default_value' => variable_get('adsense_cse_ad_location', ADSENSE_CSE_AD_LOCATION_DEFAULT),
    '#options' => array(
      'adsense_cse_loc_top_right'  => t('Top and Right'),
      'adsense_cse_loc_top_bottom' => t('Top and Bottom'),
      'adsense_cse_loc_right'      => t('Right'),
    ),
  );

  $form['blocks'] = array(
    '#type' => 'fieldset',
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
    '#title' => t('AdSense Blocks'),
  );

  $form['blocks']['adsense_cse_number_blocks'] = array(
    '#type' => 'textfield',
    '#title' => t('Number of blocks'),
    '#default_value' => variable_get('adsense_cse_number_blocks', ADSENSE_CSE_NUMBER_BLOCKS_DEFAULT),
    '#size' => 2,
    '#maxlength' => 2,
  );

  $form['#validate'][] = '_adsense_cse_settings_validate';

  return system_settings_form($form);
}

/**
 * Validate adsense_cse_settings form.
 */
function _adsense_cse_settings_validate($form, &$form_state) {
  $textbox_length = $form_state['values']['adsense_cse_textbox_length'];
  $min = 8;
  $max = 64;
  if (($textbox_length < $min ) || ($textbox_length > $max )) {
    form_set_error('adsense_cse_textbox_length', t("Text Box Length must be between !min and !max", array('!min' => $min, '!max' => $max)));
  }
  $min = ($form_state['values']['adsense_cse_ad_location'] == 'adsense_cse_loc_top_bottom') ? 500 : 795;
  $max = 10000;
  $frame_width = $form_state['values']['adsense_cse_frame_width'];
  if (($frame_width < $min ) || ($frame_width > $max )) {
    form_set_error('adsense_cse_frame_width', t("Results area width must be between !min and !max", array('!min' => $min, '!max' => $max)));
  }
  $number_blocks = $form_state['values']['adsense_cse_number_blocks'];
  if ($number_blocks < 0) {
    form_set_error('adsense_cse_number_blocks', t("Number of blocks can't be a negative number"));
  }
}
