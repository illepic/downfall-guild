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

  // tids that became group refs (remove these)
  public $terms_now_groups = array(3, 4, 60, 62, 78, 89, 90, 100, 101, 15, 16, 96, 97, 98);

  // tids that consolidated to other tids (convert)
  public $term_conversion = array(
    61 => 6, # Guild Officer, all content refs instead to tid 6 (Raid Officer)
    18 => 56, # Guild tag, updating all content refs instead to tid 56 (Guild Discussion)
    19 => 39, # Other, updating all content refs instead to tid 39 (Everything Else)
    26 => 102, # Raid, content refs to 102 instead (General Raid Discussion)
    31 => 56, # Relations, converting all content refs to 56 (Guild Discussion)
    33 => 79, # PvP, converting all refs to 79 (PvP)
    41 => 77, # Hunter, tid
    42 => 72, # Mage
    43 => 66, # Paladin
    44 => 74, # Priest
    45 => 68, # Warlock
    47 => 67, # Rogue
    48 => 73, # Shaman
    49 => 71, # Warrior
    50 => 70, # Druid
    51 => 69, # Death Knight
    53 => 63, # UI, convert to 63
  );

  // Lookup, if exists return new, if not, return what is passed in
  function convertTids($oldtid) {
    return ($this->term_conversion[$oldtid]) ? $this->term_conversion[$oldtid] : $oldtid;
  }

  /**
   * {@inheritdoc}
   */
  public function transform($value, MigrateExecutableInterface $migrate_executable, Row $row, $destination_property) {
    $nid = $value;
    $vocabulary = $this->configuration['vocabulary'];
    // Need to add in a Parent ID for our vocab that does that

    // We know the nid and the vocab, we need to find the tid
    $tids = Database::getConnection('default', 'migrate')
      ->query('SELECT termdata.tid FROM {term_data} AS termdata 
        INNER JOIN {vocabulary} as vocab ON vocab.vid = termdata.vid
        INNER JOIN {term_node} as termnode ON termnode.tid = termdata.tid
        WHERE termnode.nid = :nid AND vocab.vid = :vocabulary',
        array(':nid' => $nid, ':vocabulary' => $vocabulary))
      ->fetchAll();
//    print_r(PHP_EOL . 'All tids' . PHP_EOL);
//    print_r($tids);

    // Make a clean array
    $clean_tids = array();
    foreach($tids as $tid) {
      $clean_tids[] = $tid->tid;
    }
    // Dedupe
    $clean_tids = array_unique($clean_tids);

//    print_r(PHP_EOL . 'tids as pure array' . PHP_EOL);
//    print_r($clean_tids);

    // Remove all tids that became Group node refs, see upgrade_d6_taxonomy_term.yml
    $clean_tids = array_diff($clean_tids, $this->terms_now_groups);
//    print_r(PHP_EOL . 'Reduced tids' . PHP_EOL);
//    print_r($clean_tids);

    // Conversion from old tags to new
    $clean_tids_converted = array_map(array($this, "convertTids"), $clean_tids);
//    print_r(PHP_EOL . 'Reduced + Converted tids' . PHP_EOL);
//    print_r($clean_tids_converted);

    return $clean_tids_converted;
  }
}
