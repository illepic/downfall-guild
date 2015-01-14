<?php

/**
 * @file
 * Contains the administrative functions of the adsense_managed module.
 *
 * This file is included by the adsense_managed module, and includes the
 * settings form.
 */

/**
 * Menu callback for the adsense_managed module settings form.
 *
 * @ingroup forms
 */
function adsense_managed_settings() {
  module_load_include('inc', 'adsense_managed', 'help/adsense_managed.help');

  $form['help'] = array(
    '#type'        => 'fieldset',
    '#collapsible' => TRUE,
    '#collapsed'   => TRUE,
    '#title'       => t('Help and instructions'),
  );

  $form['help']['help'] = array(
    '#type'  => 'markup',
    '#value' => adsense_managed_help_text(),
  );

  $form['blocks'] = array(
    '#type' => 'fieldset',
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
    '#title' => t('AdSense Blocks'),
  );

  $form['blocks']['adsense_managed_number_blocks'] = array(
    '#type' => 'textfield',
    '#title' => t('Number of blocks'),
    '#default_value' => variable_get('adsense_managed_number_blocks', ADSENSE_MANAGED_NUMBER_BLOCKS_DEFAULT),
    '#size' => 2,
    '#maxlength' => 2,
  );

  $form['#validate'][] = '_adsense_managed_settings_validate';

  return system_settings_form($form);
}

/**
 * Validate adsense_managed_settings form.
 */
function _adsense_managed_settings_validate($form, &$form_state) {
  $number_blocks = $form_state['values']['adsense_managed_number_blocks'];
  if ($number_blocks < 0) {
    form_set_error('adsense_managed_number_blocks', t("Number of blocks can't be a negative number"));
  }
}
