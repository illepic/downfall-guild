<?php

/**
 * @file
 * Contains \Drupal\df_migration\Plugin\migrate\source\OgContent.
 */

namespace Drupal\df_migration\Plugin\migrate\source;

use Drupal\migrate\Plugin\migrate\source\SqlBase;

/**
 * Source plugin for OG content
 *
 * @MigrateSource(
 *   id = "og_members_og"
 * )
 */

class OgMembersOg extends SqlBase {

  /**
   * {@inheritdoc}
   */
  public function query() {
    $query = $this->select('og_uid', 'm');
    $query->join('users', 'u', 'm.uid = u.uid');
    $query
      ->fields('m', ['nid', 'uid', 'created'])
      ->fields('u', ['name']);

    return $query;
  }

  /**
   * {@inheritdoc}
   */
  public function fields() {
    $fields = [
      'nid' => $this->t('NID of group node'),
      'uid' => $this->t('User ID of group member'),
      'created' => $this->t('Creation date of content node'),
      'name' => $this->t('Name of user member'),
    ];

    return $fields;
  }

  /**
   * {@inheritdoc}
   */
  public function getIds() {
    return [
      'nid' => [
        'type' => 'integer',
        'alias' => 'm',
      ],
      'uid' => [
        'type' => 'integer',
        'alias' => 'm',
      ],
    ];
  }
}
