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
 *   id = "og_content_og"
 * )
 */

class OgContentOg extends SqlBase {

  /**
   * {@inheritdoc}
   */
  public function query() {
    $node_types = $this->configuration['node_types'] ?? false;

    $query = $this->select('og_ancestry', 'a');
    $query->join('node', 'n', 'a.nid = n.nid');
    $query
      ->fields('a', ['group_nid'])
      ->fields('n', ['nid', 'type', 'title', 'created', 'uid']);

    if ($node_types) {
      $query->condition('n.type', $node_types, 'IN');
    }

    return $query;
  }

  /**
   * {@inheritdoc}
   */
  public function fields() {
    $fields = [
      'nid' => $this->t('NID of content node'),
      'group_nid' => $this->t('NID of group node'),
      'type' => $this->t('Type of content node'),
      'title' => $this->t('Title of content node'),
      'created' => $this->t('Creation date of content node'),
      'uid' => $this->t('User ID of content node creator'),
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
        'alias' => 'a',
      ],
      'group_nid' => [
        'type' => 'integer',
        'alias' => 'a',
      ],
    ];
  }
}
