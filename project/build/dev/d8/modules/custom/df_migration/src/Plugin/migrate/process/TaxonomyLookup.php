<?php

/**
 * @file
 * Contains \Drupal\df_migration\Plugin\migrate\process\TaxonomyLookup.
 */

namespace Drupal\df_migration\Plugin\migrate\process;

use Drupal\Core\Database\Database;
use Drupal\migrate\ProcessPluginBase;
use Drupal\migrate\MigrateExecutableInterface;
use Drupal\migrate\Row;

/**
 * Lookup taxonomy terms by nid and specific vocabulary
 *
 * @MigrateProcessPlugin(
 *   id = "taxonomy_lookup"
 * )
 */
class TaxonomyLookup extends ProcessPluginBase {

  /**
   * {@inheritdoc}
   */
  public function transform($value, MigrateExecutableInterface $migrate_executable, Row $row, $destination_property) {
    $nid = $value;
    $vocabulary = $this->configuration['vocabulary'];

    // We know the nid and the vocab, we need to find the tid

    $tid = Database::getConnection('default', 'migrate')
      ->query('SELECT termdata.tid FROM {term_data} AS termdata 
        INNER JOIN {vocabulary} as vocab ON vocab.vid = termdata.vid
        INNER JOIN {term_node} as termnode ON termnode.tid = termdata.tid
        WHERE termnode.nid = :nid AND vocab.vid = :vocabulary',
        array(':nid' => $nid, ':vocabulary' => $vocabulary))
      ->fetchObject();

    return $tid->tid;
  }
}
