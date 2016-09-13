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
    $node_types = $this->configuration['node_types'] ?? false;
    $tids = $this->configuration['tids'] ?? false;

    $query = $this->select('term_node', 't');
    $query->join('node', 'n', 'n.nid = t.nid');
    $query->leftJoin('og_ancestry', 'o', 'n.nid = o.nid');
    $query
      ->fields('t', ['tid'])
      ->fields('n', ['nid', 'type', 'title', 'created', 'uid'])
      ->fields('o', ['group_nid']);

    $query->distinct();

    $query->isNull('o.group_nid');
    if ($tids) {
      $query->condition('t.tid', $tids, 'IN');
    }
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
      'tid' => $this->t('Term ID of the node'),
      'nid' => $this->t('NID of content node'),
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
        'alias' => 'n',
      ],
      'tid' => [
        'type' => 'integer',
        'alias' => 't',
      ],
    ];
  }
}
