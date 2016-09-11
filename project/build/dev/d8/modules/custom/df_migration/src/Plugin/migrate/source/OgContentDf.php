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
//    // 'blog', 'event', etc
//    $node_types = $this->configuration['node_types'] ?? false;
//    // tid: 3, gid: 12359
//    $tid_gid_map = $this->configuration['tid_gid_map'] ?? false;
//
//    // Start nid -> gid lookup (OG)
//    $og_query = $this->select('og_ancestry', 'a');
//    $og_query->join('node', 'n', 'a.nid = n.nid');
//
//    $og_query
//      ->fields('n', ['nid', 'type', 'title', 'created', 'uid'])
//      ->addField('a', 'group_nid', 'group_nid');
//
//    if ($node_types) {
//      $og_query->condition('n.type', $node_types, 'IN');
//    }
////    return $og_query;
//    // End nid -> gid lookup (OG)
//
//    // Start tid -> gid lookup (taxonomy)
//    $term_query = $this->select('term_node', 't');
//    $term_query->join('node', 'n', 't.nid = n.nid');
//
//    $term_query->fields('n', ['nid', 'type', 'title', 'created', 'uid']);
//
//    if ($tid_gid_map) {
//      // Build up sql CASE switch statement to return proper group_nid
//      $case = 'CASE';
//      foreach($tid_gid_map as $tid => $group_nid) {
//        $case .= " WHEN t.tid = $tid THEN $group_nid ";
//      }
//      $case .= 'END';
//      $term_query->addExpression($case, 'group_nid');
//
//      // Only select specific term nodes
//      $term_query->condition('t.tid', array_keys($tid_gid_map), 'IN');
//    }
//
//    if ($node_types) {
//      $term_query->condition('n.type', $node_types, 'IN');
//    }
////    return $term_query;
//    // End tid->gid lookup (taxonomy)
//


    $query = $this->select('node', 'n');
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
//        'alias' => 'nid_ogdf',
      ],
      'group_nid' => [
        'type' => 'integer',
//        'alias' => 'gid_ogdf',
      ],
    ];
  }
}
