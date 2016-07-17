<?php

/**
 * @file
 * Contains \Drupal\df_migration\Plugin\migrate\process\ExtractPoll.
 */

namespace Drupal\df_migration\Plugin\migrate\process;

use Drupal\Core\Database\Database;
use Drupal\migrate\Annotation\MigrateProcessPlugin;
use Drupal\migrate\ProcessPluginBase;
use Drupal\migrate\MigrateExecutableInterface;
use Drupal\migrate\Row;

/**
 * This plugin fixes d6 Image file names to be the actual filename from filesystem
 *
 * @MigrateProcessPlugin(
 *   id = "extract_poll"
 * )
 */
class ExtractPoll extends ProcessPluginBase {

  /**
   * {@inheritdoc}
   */
  public function transform($value, MigrateExecutableInterface $migrate_executable, Row $row, $destination_property) {
    $nid = $value;

    // Lookup in og_uid table all mentions of $value (nid)
    $poll_results = Database::getConnection('default', 'migrate')
      ->query('SELECT * FROM {poll_choices}
        WHERE nid = :nid
        ORDER BY chorder',
        array(':nid' => $nid))
      ->fetchAll();

    // Loop poll results, get total prep total
    $poll_vote_total = 0;
    foreach($poll_results as $poll_result) {
      $poll_vote_total += $poll_result->chvotes;
    }
    foreach($poll_results as $key => $poll_result) {
      $poll_results[$key]->percent = $poll_vote_total > 0 ? round($poll_result->chvotes / $poll_vote_total * 100) : 0;
    }

    $poll_list = '';
    foreach($poll_results as $poll_line) {
      $poll_list .= "<li class=\"legacy-poll__item\">
        <p>{$poll_line->chtext}</p>
        <progress value=\"{$poll_line->chvotes}\" max=\"{$poll_vote_total}\">{$poll_line->percent}%</progress>
        <p>{$poll_line->chvotes} votes / {$poll_line->percent}%</p>
       </li>";
    }
    $poll_body= "<ul class=\"legacy-poll\">{$poll_list}</ul>";

    return $poll_body;
  }
}
