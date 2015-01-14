<?php
// $Id: phpmailer.mimemail.inc,v 1.4 2009/05/07 04:33:19 sun Exp $

/**
 * @file
 * Implements PHPMailer support on behalf of Mime Mail module.
 */

module_load_include('inc', 'phpmailer', 'includes/phpmailer.class');

/**
 * Send out an e-mail.
 *
 * @param $message
 *   Mime Mail message array.
 */
function mimemail_phpmailer_send($message) {
  static $mail;

  if (!isset($mail)) {
    $mail = new DrupalPHPMailer();
    // Keep linefeed style in sync.
    $mail->LE = variable_get('mimemail_crlf', "\n");
  }

  // Extract and assign e-mail addresses required for SMTP.
  // Display names are not required. Leave header intact.

  // Parse 'From' e-mail address.
  $address = phpmailer_parse_address($message['sender']);
  $mail->From = $address[0]['mail'];

  if (variable_get('phpmailer_debug_email', '') === '') {
    // Set recipients.
    foreach (phpmailer_parse_address($message['address']) as $address) {
      $mail->AddAddress($address['mail']);
    }
    // Extract CCs and BCCs from headers.
    if (isset($message['headers']['CC'])) {
      foreach (phpmailer_parse_address($message['headers']['CC']) as $address) {
        $mail->AddCC($address['mail']);
      }
    }
    if (isset($message['headers']['BCC'])) {
      foreach (phpmailer_parse_address($message['headers']['BCC']) as $address) {
        $mail->AddBCC($address['mail']);
      }
    }
  }
  else {
    // Reroute to debug e-mail address.
    $message['address'] = variable_get('phpmailer_debug_email', '');
    $mail->AddAddress($message['address']);
  }
  unset($message['headers']['CC'], $message['headers']['BCC']);

  if ($mail->SMTPDebug) {
    ob_start();
  }

  $message['headers']['Date'] = $mail->RFCDate();
  if ($message['address']) {
    $message['headers']['To'] = $message['address'];
  }
  $message['headers']['Subject'] = $message['subject'];
  // FIXME SpamAssassin says INVALID_MSGID to PHPMailer's generated Message-ID. 06/04/2009 smk
//  if (!isset($message['headers']['Message-ID'])) {
//    $message['headers']['Message-ID'] = sprintf("<%s@%s>", md5(uniqid(time())), $mail->ServerHostname());
//  }
  $header = mimemail_rfc_headers($message['headers']) . $mail->LE . $mail->LE;

  if (!($result = $mail->SmtpSend($header, $message['body']))) {
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

