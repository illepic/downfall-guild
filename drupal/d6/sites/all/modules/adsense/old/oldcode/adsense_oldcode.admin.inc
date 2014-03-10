<?php

/**
 * @file
 * Contains the administrative functions of the adsense_oldcode module.
 *
 * This file is included by the adsense_oldcode module, and includes the
 * settings form.
 */

/**
 * Menu callback for the adsense_oldcode module settings form.
 *
 * @ingroup forms
 */
function adsense_oldcode_settings() {
  $form['blocks'] = array(
    '#type' => 'fieldset',
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
    '#title' => t('AdSense Blocks'),
  );

  $form['blocks']['adsense_oldcode_number_blocks'] = array(
    '#type' => 'textfield',
    '#title' => t('Number of blocks'),
    '#default_value' => variable_get('adsense_oldcode_number_blocks', ADSENSE_OLDCODE_NUMBER_BLOCKS_DEFAULT),
    '#size' => 2,
    '#maxlength' => 2,
  );

  $form['types_colors'] = array(
    '#type'        => 'fieldset',
    '#collapsible' => TRUE,
    '#collapsed'   => TRUE,
    '#title'       => t('Ad groups'),
  );

  // Add Farbtastic color picker
  drupal_add_css('misc/farbtastic/farbtastic.css', 'module', 'all', FALSE);
  drupal_add_js('misc/farbtastic/farbtastic.js');
  drupal_add_js(drupal_get_path('module', 'adsense_oldcode') .'/adsense_oldcode.js');

  for ($group=1; $group <= ADSENSE_MAX_GROUPS ; $group++) {
    $form['types_colors']['groups'][$group] = array(
      '#type' => 'fieldset',
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
      '#title' => t('Group @group attributes', array('@group' => $group .' '. variable_get('adsense_group_title_'. $group, ADSENSE_GROUP_TITLE_DEFAULT))),
    );

    $form['types_colors']['groups'][$group]['adsense_group_title_'. $group] = array(
      '#type'          => 'textfield',
      '#title'         => t('Title'),
      '#default_value' => variable_get('adsense_group_title_'. $group, ADSENSE_GROUP_TITLE_DEFAULT),
      '#size'          => 100,
      '#maxlength'     => 100,
      '#description'   => t('Title of the group.'),
    );

    $form['types_colors']['groups'][$group]['adsense_ad_type_'. $group] = array(
      '#type' => 'radios',
      '#title' => t('Ad type'),
      '#default_value' => variable_get('adsense_ad_type_'. $group, ADSENSE_AD_TYPE_DEFAULT),
      '#options' => array(t('Text'), t('Image'), t('Both')),
    );

    $form['types_colors']['groups'][$group]['colorpicker'] = array(
      '#type' => 'markup',
      '#value' => "<div id='colorpicker-$group' style='float: right;'></div>",
    );

    $form['types_colors']['groups'][$group]['adsense_color_text_'. $group] = array(
      '#type' => 'textfield',
      '#title' => t('Text color'),
      '#default_value' => variable_get('adsense_color_text_'. $group, ADSENSE_COLOR_TEXT_DEFAULT),
      '#size' => 7,
      '#maxlength' => 7,
    );

    $form['types_colors']['groups'][$group]['adsense_color_border_'. $group] = array(
      '#type' => 'textfield',
      '#title' => t('Border color'),
      '#default_value' => variable_get('adsense_color_border_'. $group, ADSENSE_COLOR_BORDER_DEFAULT),
      '#size' => 7,
      '#maxlength' => 7,
    );

    $form['types_colors']['groups'][$group]['adsense_color_bg_'. $group] = array(
      '#type' => 'textfield',
      '#title' => t('Background color'),
      '#default_value' => variable_get('adsense_color_bg_'. $group, ADSENSE_COLOR_BG_DEFAULT),
      '#size' => 7,
      '#maxlength' => 7,
    );

    $form['types_colors']['groups'][$group]['adsense_color_link_'. $group] = array(
      '#type' => 'textfield',
      '#title' => t('Title color'),
      '#default_value' => variable_get('adsense_color_link_'. $group, ADSENSE_COLOR_LINK_DEFAULT),
      '#size' => 7,
      '#maxlength' => 7,
    );

    $form['types_colors']['groups'][$group]['adsense_color_url_'. $group] = array(
      '#type' => 'textfield',
      '#title' => t('URL color'),
      '#default_value' => variable_get('adsense_color_url_'. $group, ADSENSE_COLOR_URL_DEFAULT),
      '#size' => 7,
      '#maxlength' => 7,
    );

    $form['types_colors']['groups'][$group]['adsense_alt_'. $group] = array(
      '#type' => 'select',
      '#title' => t('Alternate URL color'),
      '#default_value' => variable_get('adsense_alt_'. $group, ADSENSE_ALT_DEFAULT),
      '#options' => array(t('None'), t('Alternate URL'), t('Alternate color')),
    );

    $form['types_colors']['groups'][$group]['adsense_alt_info_'. $group] = array(
      '#type' => 'textfield',
      '#title' => t('Alternate info'),
      '#default_value' => variable_get('adsense_alt_info_'. $group, ADSENSE_ALT_INFO_DEFAULT),
      '#size' => 100,
      '#maxlength' => 100,
      '#description' => t('Enter either 6 letter alternate color code, or alternate URL to use'),
    );

    $form['types_colors']['groups'][$group]['adsense_ui_features_'. $group] = array(
      '#type' => 'select',
      '#title' => t('Rounded corners'),
      '#default_value' => variable_get('adsense_ui_features_'. $group, ADSENSE_UI_FEATURES_DEFAULT),
      '#options' => array(
        'rc:0' => 'Square',
        'rc:6' => 'Slightly rounded',
        'rc:10' => 'Very rounded',
      ),
      '#description' => t('Choose type of round corners'),
    );
  }

  $form['channels'] = array(
    '#type' => 'fieldset',
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#title' => t('Custom channels'),
    '#description' => t('Enter up to !channels custom channels that you have configured in Google AdSense. If you are not using custom channels, or you are only using URL channels, then leave this empty.', array('!channels' => ADSENSE_MAX_CHANNELS)),
  );

  for ($channel=1; $channel <= ADSENSE_MAX_CHANNELS ; $channel++) {
    $form['channels']['adsense_ad_channel_'. $channel] = array(
      '#type' => 'textfield',
      '#title' => t('Custom channel ID') .' '. $channel,
      '#default_value' => variable_get('adsense_ad_channel_'. $channel, ADSENSE_AD_CHANNEL_DEFAULT),
      '#size' => 30,
      '#maxlength' => 30,
    );
  }

  $form['#validate'][] = '_adsense_oldcode_settings_validate';

  return system_settings_form($form);
}

/**
 * Validate adsense_oldcode_settings form.
 */
function _adsense_oldcode_settings_validate($form, &$form_state) {
  $number_blocks = $form_state['values']['adsense_oldcode_number_blocks'];
  if ($number_blocks < 0) {
    form_set_error('adsense_oldcode_number_blocks', t("Number of blocks can't be a negative number"));
  }

  $colors = array(
    'adsense_color_border_',
    'adsense_color_bg_',
    'adsense_color_link_',
    'adsense_color_url_',
    'adsense_color_text_',
  );

  for ($group = 1; $group <= ADSENSE_MAX_GROUPS ; $group++) {
    foreach ($colors as $field_name) {
      $field_value = $form_state['values'][$field_name . $group];
      $form_state['values'][$field_name . $group] = drupal_strtoupper($field_value);
      if (!preg_match('/#[0-9A-F]{6}/i', $field_value)) {
        form_set_error($field_name . $group, t("Color must be between #000000 and #FFFFFF"));
      }
    }
  }
}
