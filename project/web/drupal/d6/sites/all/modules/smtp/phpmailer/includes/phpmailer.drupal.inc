<?php
// $Id: phpmailer.drupal.inc,v 1.6 2009/06/10 13:07:28 smk Exp $

/**
 * @file
 * Implements PHPMailer support on behalf of Drupal core.
 */

module_load_include('inc', 'phpmailer', 'includes/phpmailer.class');

/**
 * Send out an e-mail.
 *
 * @param $message
 *   Message array structure.
 */
function phpmailer_send($message) {
  static $mail;

  if (!isset($mail)) {
    $mail = new DrupalPHPMailer();
  }

  // Parse 'From' e-mail address.
  $address = phpmailer_parse_address($message['from']);
  $mail->From = $address[0]['mail'];
  if ($address[0]['name'] != '') {
    $mail->FromName = $address[0]['name'];
  }
  unset($message['headers']['From']);

  if (variable_get('phpmailer_debug_email', '') === '') {
    // Set recipients.
    foreach (phpmailer_parse_address($message['to']) as $address) {
      $mail->AddAddress($address['mail'], $address['name']);
    }
    // Extract CCs and BCCs from headers.
    if (isset($message['headers']['CC'])) {
      foreach (phpmailer_parse_address($message['headers']['CC']) as $address) {
        $mail->AddCC($address['mail'], $address['name']);
      }
    }
    if (isset($message['headers']['BCC'])) {
      foreach (phpmailer_parse_address($message['headers']['BCC']) as $address) {
        $mail->AddBCC($address['mail'], $address['name']);
      }
    }
  }
  else {
    // Reroute to debug e-mail address.
    $mail->AddAddress(variable_get('phpmailer_debug_email', ''));
  }
  unset($message['headers']['CC'], $message['headers']['BCC']);

  // Extract Content-Type and charset.
  if (isset($message['headers']['Content-Type'])) {
    $content_type = explode(';', $message['headers']['Content-Type']);
    $mail->ContentType = trim(array_shift($content_type));
    foreach ($content_type as $param) {
      $param = explode('=', $param, 2);
      $key = trim($param[0]);
      if ($key == 'charset') {
        $mail->CharSet = trim($param[1]);
      }
      else {
        $mail->ContentType .= '; ' . $key . '=' . trim($param[1]);
      }
    }
    unset($message['headers']['Content-Type']);
  }

  // Set additional properties.
  $properties = array(
    'X-Priority'                => 'Priority',
    'Content-Transfer-Encoding' => 'Encoding',
    'Sender'                    => 'Sender',
    'Message-ID'                => 'MessageID',
    // Custom property.
    // @see DrupalPHPMailer::CreateHeader()
    'Return-Path'               => 'ReturnPath',
  );
  foreach ($properties as $source => $property) {
    if (isset($message['headers'][$source])) {
      $mail->$property = $message['headers'][$source];
      unset($message['headers'][$source]);
    }
  }

  // This one is always set by PHPMailer.
  unset($message['headers']['MIME-Version']);

  // Add remaining header lines.
  // Note: Any header lines MUST already be checked by the caller for unwanted
  // newline characters to avoid header injection.
  // @see PHPMailer::SecureHeader()
  foreach ($message['headers'] as $key => $value) {
    $mail->AddCustomHeader("$key:$value");
  }

  $mail->Subject = $message['subject'];
  $mail->Body = $message['body'];

  if ($mail->SMTPDebug) {
    ob_start();
  }

  if (!($result = $mail->Send())) {
    watchdog('phpmailer', $mail->ErrorInfo, NULL, WATCHDOG_ERROR);
  }

  // Reset object properties.
  $mail->Reset();

  if ($mail->SMTPDebug) {
    if ($debug = ob_get_contents()) {
      drupal_set_message($debug);
    }
    ob_end_clean();
  }

  return $result;
}

