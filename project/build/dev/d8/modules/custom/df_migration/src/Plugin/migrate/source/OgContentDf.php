<?php

/**
 * @file
 * Contains \Drupal\df_migration\Plugin\migrate\source\OgContent.
 */

namespace Drupal\df_migration\Plugin\migrate\source;

use Drupal\migrate\Plugin\migrate\source\SqlBase;

/**
 * Source plugin for OG content and content terms unique to Downfall's model
 *
 * @MigrateSource(
 *   id = "og_content_df"
 * )
 */

class OgContentDf extends SqlBase {

  /**
   * {@inheritdoc}
   */
  public function query() {

    $node_types = $this->configuration['node_types'] ?? false;

    $tid_gid_map = $this->configuration['tid_gid_map'] ?? false;
    $tids = array_keys($tid_gid_map);

    $query = $this->select('node', 'n');
    $query->fields('n', ['nid', 'type', 'title', 'created', 'uid']);

    $query->addField('o', 'group_nid', 'group_nid');
    $query->addField('t', 'tid', 'tid');

    $query->addExpression('CASE WHEN o.group_nid IS NOT NULL THEN o.group_nid WHEN t.tid = 3 THEN 12359 WHEN t.tid = 4 THEN 12360 WHEN t.tid = 15 THEN 12359 WHEN t.tid = 16 THEN 12360 WHEN t.tid = 60 THEN 7393 WHEN t.tid = 62 THEN 10671 WHEN t.tid = 78 THEN 8056 WHEN t.tid = 89 THEN 7365 WHEN t.tid = 90 THEN 6593 WHEN t.tid = 96 THEN 7365 WHEN t.tid = 97 THEN 6593 WHEN t.tid = 98 THEN 7393 WHEN t.tid = 100 THEN 12361 WHEN t.tid = 101 THEN 9406 ELSE NULL END', 'smart_gid');

    $query->distinct();

    $query->leftJoin('og_ancestry', 'o', 'o.nid = n.nid');
    $query->leftJoin('term_node', 't', 't.nid = n.nid AND o.group_nid IS NULL');

    $query->condition('n.type', $node_types, 'IN');

    $gid_tid_not_null = $query->orConditionGroup()->isNotNull('o.group_nid')->isNotNull('t.tid');
    $query->condition($gid_tid_not_null);

    $tids_specific = $query->orConditionGroup()->condition('t.tid', $tids, 'IN')->isNull('t.tid');
    $query->condition($tids_specific);

    return $query;
  }

  /**
   * {@inheritdoc}
   */
  public function fields() {
    $fields = [
      'nid' => $this->t('NID of content node'),
      'type' => $this->t('Type of content node'),
      'title' => $this->t('Title of content node'),
      'created' => $this->t('Creation date of content node'),
      'uid' => $this->t('User ID of content node creator'),
      'group_nid' => $this->t('NID of group node'),
      'tid' => $this->t('Term ID for nodes only tagged (no group)'),
      'smart_gid' => $this->t('Magic lookup for tid -> gid')
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
      'smart_gid' => [
        'type' => 'integer',
      ],
//      'group_nid' => [
//        'type' => 'integer',
//        'alias' => 'o',
//      ],
//      'tid' => [
//        'type' => 'integer',
//        'alias' => 't',
//      ],
    ];
  }
}
