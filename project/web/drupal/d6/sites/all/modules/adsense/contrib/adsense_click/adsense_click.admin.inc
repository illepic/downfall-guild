<?php

/**
 * @file
 * Contains the administrative functions of the adsense_click module.
 *
 * This file is included by the adsense_click module, and includes the
 * settings form.
 */

function adsense_click_admin_settings() {
  $form['click_tracking'] = array(
    '#type'  => 'fieldset',
    '#title' => t('Click tracking'),
  );

  $form['click_tracking']['adsense_click_tracking'] = array(
    '#type'          => 'checkbox',
    '#title'         => t('Enable AdSense click tracking?'),
    '#default_value' => variable_get('adsense_click_tracking', ADSENSE_CLICK_TRACKING_DEFAULT),
    '#description'   => t('Logs IP and time of <a href=!url>AdSense clicks</a>. This can be very useful in tracking which of your pages generate the most clicks, as well as help if click fraud is suspected.', array('!url' => url('admin/reports/adsense'))),
  );
  $form['click_tracking']['adsense_click_tracking_name_resolve'] = array(
    '#type'          => 'checkbox',
    '#title'         => t('Enable name resolution of IP addresses?'),
    '#default_value' => variable_get('adsense_click_tracking_name_resolve', ADSENSE_CLICK_TRACKING_NAME_RESOLVE_DEFAULT),
    '#description'   => t('Display the domain name instead of the IP address. This can slow down the display of the logs page and tie up a PHP process for several seconds. On some hosting providers it may not be available.'),
  );

  return system_settings_form($form);
}
