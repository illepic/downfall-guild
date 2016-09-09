<?php

/**
 * @file
 * Contains \Drupal\df_migration\Plugin\migrate\source\GroupContentTaxonomy.
 */

namespace Drupal\df_migration\Plugin\migrate\source;

use Drupal\migrate\Plugin\migrate\source\SqlBase;

/**
 * Source plugin for OG content
 *
 * @MigrateSource(
 *   id = "group_content_taxonomy"
 * )
 */

class GroupContentTaxonomy extends SqlBase {

  /**
   * {@inheritdoc}
   */
  public function query() {
    $tids = $this->configuration['tids'] ?? false;

    $query = $this->select('term_node', 't');
    $query->join('node', 'n', 't.nid = n.nid');
    $query
      ->fields('t', ['nid', 'tid'])
      ->fields('n', ['type', 'title', 'created', 'uid']);

    if ($tids) {
      $query->condition('t.tid', $tids, 'IN');
    }

    return $query;
  }

  /**
   * {@inheritdoc}
   */
  public function fields() {
    $fields = [
      'nid' => $this->t('NID of content node'),
      'tid' => $this->t('Term ID of the node'),
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
        'alias' => 't',
      ],
      'tid' => [
        'type' => 'integer',
        'alias' => 't',
      ],
    ];
  }
}
