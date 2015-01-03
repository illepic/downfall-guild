<?php

/**
 * @file
 * Contains the administrative functions of the adsense module.
 *
 * This file is included by the core adsense module, and includes the
 * settings form.
 */

/**
 * Menu callback for the adsense module settings form.
 *
 * @ingroup forms
 */
function adsense_main_settings() {
  module_load_include('inc', 'adsense', 'help/adsense.help');
  module_load_include('inc', 'adsense', 'includes/adsense.search_options');

  $form['help'] = array(
    '#type'        => 'fieldset',
    '#collapsible' => TRUE,
    '#collapsed'   => TRUE,
    '#title'       => t('Help and instructions'),
  );

  $form['help']['help'] = array(
    '#type'  => 'markup',
    '#value' => adsense_help_text(),
  );

  $form['visibility'] = array(
    '#type' => 'fieldset',
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
    '#title' => t('Visibility'),
  );

  $form['visibility']['adsense_visibility'] = array(
    '#type' => 'radios',
    '#title' => t('Show AdSense on specific pages'),
    '#default_value' => variable_get('adsense_visibility', ADSENSE_VISIBILITY_DEFAULT),
    '#options' => array(t('Show on every page except the listed pages.'), t('Show on only the listed pages.')),
  );

  $form['visibility']['adsense_access_pages'] = array(
    '#type' => 'textarea',
    '#default_value' => variable_get('adsense_access_pages', ADSENSE_ACCESS_PAGES_DEFAULT),
    '#rows' => 3,
    '#description' => t("Enter one page per line as Drupal paths. The '*' character is a wildcard. Example paths are  %blog for the blog page and %blog-wildcard for every personal blog. %front is the front page.", array('%blog' => 'blog', '%blog-wildcard' => 'blog/*', '%front' => '<front>')),
    '#wysiwyg' => FALSE,
  );

  $access = user_access('use PHP for ad visibility');

  if ($form['visibility']['adsense_visibility']['#default_value'] == 2 && !$access) {
    $form['visibility']['adsense_visibility'] = array('#type' => 'value', '#value' => 2);
    $form['visibility']['adsense_access_pages'] = array('#type' => 'value', '#value' => $form['visibility']['adsense_access_pages']['#default_value']);
  }
  elseif ($access) {
    $form['visibility']['adsense_visibility']['#options'][] = t('Show if the following PHP code returns <code>TRUE</code> (PHP-mode, experts only).');
    $form['visibility']['adsense_access_pages']['#description'] .= ' '. t('If the PHP-mode is chosen, enter PHP code between %php. Note that executing incorrect PHP-code can break your Drupal site.', array('%php' => '<?php ?>'));
  }

  $form['advanced'] = array(
    '#type' => 'fieldset',
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
    '#title' => t('Advanced options'),
  );

  $form['advanced']['adsense_unblock_ads'] = array(
    '#type' => 'checkbox',
    '#title' => t('Display anti ad-block request?'),
    '#default_value' => variable_get('adsense_unblock_ads', ADSENSE_UNBLOCK_ADS_DEFAULT),
    '#description' => t("EXPERIMENTAL! Enabling this feature will add a mechanism that tries to detect when adblocker software is in use, displaying a polite request to the user to enable ads on this site. [!moreinfo]", array('!moreinfo' => l(t('More information'), 'http://easylist.adblockplus.org/blog/2013/05/10/anti-adblock-guide-for-site-admins'))),
  );

  $form['advanced']['adsense_test_mode'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable test mode?'),
    '#default_value' => variable_get('adsense_test_mode', ADSENSE_TEST_MODE_DEFAULT),
    '#description' => t('This enables you to test the AdSense module settings. This can be useful in some situations: for example, testing whether revenue sharing is working properly or not without having to display real ads on your site. It is best to test this after you log out.'),
  );

  $form['advanced']['adsense_disable'] = array(
    '#type' => 'checkbox',
    '#title' => t('Disable Google AdSense ads?'),
    '#default_value' => variable_get('adsense_disable', ADSENSE_DISABLE_DEFAULT),
    '#description' => t('This disables all display of Google AdSense ads from your web site. This is useful in certain situations, such as site upgrades, or if you make a copy of the site for development and test purposes.'),
  );

  $form['advanced']['adsense_placeholder'] = array(
    '#type' => 'checkbox',
    '#title' => t('Placeholder when ads are disabled?'),
    '#default_value' => variable_get('adsense_placeholder', ADSENSE_PLACEHOLDER_DEFAULT),
    '#description' => t('This causes an empty box to be displayed in place of the ads when they are disabled.'),
  );

  $form['advanced']['adsense_placeholder_text'] = array(
    '#type' => 'textarea',
    '#title' => t('Placeholder text to display'),
    '#default_value' => variable_get('adsense_placeholder_text', ADSENSE_PLACEHOLDER_TEXT_DEFAULT),
    '#rows' => 3,
    '#description' => t('Enter any text to display as a placeholder when ads are disabled.'),
  );

  $form['advanced']['adsense_section_targeting'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable AdSense section targeting?'),
    '#default_value' => variable_get('adsense_section_targeting', ADSENSE_SECTION_TARGETING_DEFAULT),
    '#description' => t('This better targets Google ads to the teaser and body of nodes.'),
  );

  $form['secret'] = array(
    '#type' => 'fieldset',
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#title' => t('Undocumented options'),
    '#description' => t("Warning: Use of these options is AT YOUR OWN RISK. Google will never generate an ad with any of these options, so using one of them is a violation of Google AdSense's Terms and Conditions. USE OF THESE OPTIONS MAY RESULT IN GETTING BANNED FROM THE PROGRAM. You may lose all the revenue accumulated in your account. FULL RESPONSABILITY FOR THE USE OF THESE OPTIONS IS YOURS. In other words, don't complain to the authors about getting banned, even if using one of these options was provided as a solution to a reported problem."),
  );

  $form['secret']['agreed'] = array(
    '#type' => 'fieldset',
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#title' => t('I agree'),
  );

  $form['secret']['agreed']['adsense_secret_adtest'] = array(
    '#type' => 'checkbox',
    '#title' => t("Use Google's AdSense test option?"),
    '#default_value' => variable_get('adsense_secret_adtest', ADSENSE_SECRET_ADTEST_DEFAULT),
    '#description' => t('With this option set, Google will not count any clicks or page impressions. Revenue is not generated. Make sure that you disable this option in production servers. [!statement]', array('!statement' => l(t('Unofficial statement'), 'http://adsense-es.blogspot.com/2007/01/impresiones-de-mis-propios-anuncios-en.html'))),
  );

  $form['secret']['agreed']['adsense_secret_language'] = array(
    '#type' => 'select',
    '#title' => t('Language to display ads'),
    '#default_value' => variable_get('adsense_secret_language', ADSENSE_SECRET_LANGUAGE_DEFAULT),
    '#options' => array_merge(array(ADSENSE_SECRET_LANGUAGE_DEFAULT => 'Set by Google'), _adsense_search_options_language()),
  );

  return system_settings_form($form);
}

/**
 * Menu callback for the adsense publisher ID settings form.
 *
 * @ingroup forms
 */
function adsense_id_settings() {
  module_load_include('inc', 'adsense', 'help/adsense_id_help');

  $form['help'] = array(
    '#type'        => 'fieldset',
    '#collapsible' => TRUE,
    '#collapsed'   => TRUE,
    '#title'       => t('Help and instructions'),
  );

  $form['help']['help'] = array(
    '#type'  => 'markup',
    '#value' => adsense_id_help_text(),
  );

  $form['adsense_basic_id'] = array(
    '#type'          => 'textfield',
    '#title'         => t('Site Google AdSense Publisher ID'),
    '#required'      => TRUE,
    '#default_value' => variable_get('adsense_basic_id', ADSENSE_BASIC_ID_DEFAULT),
    '#description'   => t('This is the Google AdSense Publisher ID for the site owner. It is used if no other ID is suitable. Get this in your Google Adsense account. It should be similar to %id.', array('%id' => 'pub-9999999999999')),
  );

  $options = _adsense_id_settings_client_id_mods();
  if (count($options) > 1) {
    $form['adsense_id_module'] = array(
      '#type'          => 'radios',
      '#title'         => t('Publisher ID module'),
      '#default_value' => variable_get('adsense_id_module', ADSENSE_ID_MODULE_DEFAULT),
      '#options'       => $options,
    );
  }
  else {
    $form['adsense_id_module'] = array(
      '#type'  => 'hidden',
      '#value' => $options['adsense_basic'],
    );
  }

  $form['#validate'][] = '_adsense_id_settings_validate';

  return system_settings_form($form);
}

/**
 * Validate adsense_id_settings form.
 */
function _adsense_id_settings_validate($form, &$form_state) {
  // Trim remaning whitespace.
  $form_state['values']['adsense_basic_id'] = trim($form_state['values']['adsense_basic_id']);

  // Verify it's a valid Adsense publisher ID.
  if (!preg_match('/^pub-[0-9]+$/', $form_state['values']['adsense_basic_id'])) {
    form_set_error('adsense_basic_id', t('A valid Google AdSense Publisher ID is case sensitive and formatted like %id.', array('%id' => 'pub-9999999999999')));
  }
}

/**
 * Search for the available Publisher ID modules
 *
 * @return
 *   array of selectable Publisher ID functions
 */
function _adsense_id_settings_client_id_mods() {
  $ret['adsense_basic'] = 'Always use the site Publisher ID.';

  $funcs = get_defined_functions();
  foreach ($funcs['user'] as $func) {
    if (preg_match('!_adsense$!', $func)) {
      $settings = $func('settings');
      $ret[$func] = $settings['name'];
      if (!empty($settings['desc'])) {
        $ret[$func] .= "<div style='margin-left: 2.5em;' class='description'>{$settings['desc']}</div>";
      }
    }
  }
  return $ret;
}
