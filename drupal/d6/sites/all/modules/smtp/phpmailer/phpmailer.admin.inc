<?php
// $Id: phpmailer.admin.inc,v 1.8 2009/06/10 13:01:36 smk Exp $

/**
 * @file
 * Administrative functions for PHPMailer integration module.
 */

/**
 * Form builder for both the Mime Mail hook and our own menu callback.
 */
function phpmailer_settings_form() {
  // Override the 'smtp_library' variable.
  $smtp_library = variable_get('smtp_library', '');
  if (variable_get('smtp_on', 0)) {
    if (!strpos($smtp_library, 'phpmailer')) {
      variable_set('smtp_library', drupal_get_filename('module', 'phpmailer'));
    }
  }
  else {
    if (strpos($smtp_library, 'phpmailer')) {
      variable_del('smtp_library');
    }
  }

  if (!variable_get('mimemail_alter', 0)) {
    $form['smtp_on'] = array(
      '#type' => 'checkbox',
      '#title' => t('Use PHPMailer to send e-mails'),
      '#default_value' => variable_get('smtp_on', 0),
      '#description' => t('When enabled, PHPMailer will be used for e-mail transport.'),
    );
  }
  else {
    $form['smtp_on'] = array(
      '#type' => 'value',
      '#value' => 0,
    );
  }

  $form['server']['smtp_host'] = array(
    '#type' => 'textfield',
    '#title' => t('Primary SMTP server'),
    '#default_value' => variable_get('smtp_host', 'localhost'),
    '#description' => t('The host name or IP address of your primary SMTP server.  Use !gmail-smtp for Google Mail.', array('!gmail-smtp' => '<code>smtp.gmail.com</code>')),
    '#required' => TRUE,
  );
  $form['server']['smtp_hostbackup'] = array(
    '#type' => 'textfield',
    '#title' => t('Backup SMTP server'),
    '#default_value' => variable_get('smtp_hostbackup', ''),
    '#description' => t('Optional host name or IP address of a backup server, if the primary server fails.  You can override the default port by appending it to the host name separated with a colon.  Example: !hostname', array('!hostname' => '<code>localhost:465</code>')),
  );
  $form['server']['smtp_port'] = array(
    '#type' => 'textfield',
    '#title' => t('SMTP port'),
    '#size' => 5,
    '#maxlength' => 5,
    '#default_value' => variable_get('smtp_port', '25'),
    '#description' => t('The standard SMTP port is 25, for Google Mail use 465.'),
    '#required' => TRUE,
  );
  $form['server']['smtp_protocol'] = array(
    '#type' => 'select',
    '#title' => t('Use secure protocol'),
    '#default_value' => variable_get('smtp_protocol', ''),
    '#options' => array('' => t('No'), 'ssl' => t('SSL'), 'tls' => t('TLS')),
    '#description' => t('Whether to use an encrypted connection to communicate with the SMTP server.  Google Mail requires %SSL.', array('%SSL' => 'SSL')),
  );
  if (!function_exists('openssl_open')) {
    $form['server']['smtp_protocol']['#default_value'] = '';
    $form['server']['smtp_protocol']['#disabled'] = TRUE;
    $form['server']['smtp_protocol']['#description'] .= ' ' . t('Note: This option has been disabled since your PHP installation does not seem to have support for OpenSSL.');
    variable_set('smtp_protocol', '');
  }

  $form['auth'] = array(
    '#type' => 'fieldset',
    '#title' => t('SMTP authentication'),
    '#description' => t('Leave blank if your SMTP server does not require authentication.'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  $form['auth']['smtp_username'] = array(
    '#type' => 'textfield',
    '#title' => t('Username'),
    '#default_value' => variable_get('smtp_username', ''),
    '#description' => t('For Google Mail, enter your username including "@gmail.com".'),
  );
  $form['auth']['smtp_password'] = array(
    '#type' => 'textfield',
    '#title' => t('Password'),
    '#default_value' => variable_get('smtp_password', ''),
  );

  $form['advanced'] = array(
    '#type' => 'fieldset',
    '#title' => t('Advanced SMTP settings'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  $form['advanced']['smtp_keepalive'] = array(
    '#type' => 'checkbox',
    '#title' => t('Keep connection alive'),
    '#default_value' => variable_get('smtp_keepalive', 0),
    '#description' => t('Whether to reuse an existing connection during a request.  Improves performance when sending a lot of e-mails at once.'),
  );
  $form['advanced']['smtp_fromname'] = array(
    '#type' => 'textfield',
    '#title' => t('"From" name'),
    '#default_value' => variable_get('smtp_fromname', ''),
    '#description' => t('Enter a name that should appear as the sender for all messages.  If left blank the site name will be used instead: %sitename.', array('%sitename' => variable_get('site_name', 'Drupal'))),
  );
  $form['advanced']['smtp_debug'] = array(
    '#type' => 'select',
    '#title' => t('Debug level'),
    '#default_value' => variable_get('smtp_debug', 0),
    '#options' => array(0 => t('Disabled'), 1 => t('Errors only'), 2 => t('Server responses'), 4 => t('Full communication')),
    '#description' => t("Debug the communication with the SMTP server.  You normally shouldn't enable this unless you're trying to debug e-mail sending problems."),
  );

  // If an address was given, send a test email message.
  $test_address = variable_get('smtp_test_address', '');
  if ($test_address != '') {
    drupal_set_message(t('A test e-mail has been sent to %email.  You may want to <a href="!watchdog">check the logs</a> for any error messages.', array('%email' => $test_address, '!watchdog' => url('admin/reports/dblog'))));
    drupal_mail('phpmailer', 'test', $test_address, NULL);
    variable_del('smtp_test_address');
  }

  $form['test'] = array(
    '#type' => 'fieldset',
    '#title' => t('Test configuration'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  $form['test']['smtp_test_address'] = array(
    '#type' => 'textfield',
    '#title' => t('Recipient'),
    '#default_value' => '',
    '#description' => t('Type in an address to have a test e-mail sent there.'),
  );
  if (!strpos(variable_get('smtp_library', ''), 'phpmailer') && module_exists('mimemail') && variable_get('mimemail_alter', 0)) {
    $form['test']['preview'] = array(
      '#type' => 'item',
      '#title' => t('Preview'),
      '#value' => t('For theming of HTML mails sent via Mime Mail, you can <a href="@preview-url" target="_blank">preview an example mail</a>.', array('@preview-url' => url('phpmailer/preview'))),
    );
  }

  if (!module_exists('mimemail')) {
    return system_settings_form($form);
  }
  return $form;
}

/**
 * Implementation of hook_mail().
 */
function phpmailer_mail($key, &$message, $params) {
  $message['subject'] = t('PHPMailer test e-mail');
  $message['body'][] = t('Your site is properly configured to send e-mails using the PHPMailer library.');
}

