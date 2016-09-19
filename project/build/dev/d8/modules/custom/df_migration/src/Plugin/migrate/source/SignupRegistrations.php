<?php

/**
 * @file
 * Contains \Drupal\df_migration\Plugin\migrate\source\SignupRegistrations.
 */

namespace Drupal\df_migration\Plugin\migrate\source;

use Drupal\migrate\Plugin\migrate\source\SqlBase;

/**
 * Source plugin for OG content
 *
 * @MigrateSource(
 *   id = "signup_registrations"
 * )
 */

class SignupRegistrations extends SqlBase {

  /**
   * {@inheritdoc}
   */
  public function query() {
    $query = $this->select('signup_log', 's');
    $query->fields('s', ['uid', 'nid', 'signup_time', 'form_data']);

    return $query;
  }

  /**
   * {@inheritdoc}
   */
  public function fields() {
    $fields = [
      'uid' => $this->t('User id of signup'),
      'nid' => $this->t('Node id user is signing up for'),
      'signup_time' => $this->t('Time of signup'),
      'form_data' => $this->t('Blob of data associated with signup, like name and phone'),
    ];

    return $fields;
  }

  /**
   * {@inheritdoc}
   */
  public function getIds() {
    return [
      'uid' => [
        'type' => 'integer',
        'alias' => 's',
      ],
      'nid' => [
        'type' => 'integer',
        'alias' => 's',
      ],
    ];
  }
}
