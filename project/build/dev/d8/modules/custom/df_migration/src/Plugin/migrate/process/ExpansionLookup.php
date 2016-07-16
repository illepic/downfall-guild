<?php

/**
 * @file
 * Contains \Drupal\df_migration\Plugin\migrate\process\ExpansionLookup.
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
 *   id = "expansion_lookup"
 * )
 */
class ExpansionLookup extends ProcessPluginBase {

  /**
   * {@inheritdoc}
   */
  public function transform($value, MigrateExecutableInterface $migrate_executable, Row $row, $destination_property) {

    // Expansion release dates
    $vanilla = new \DateTime('24-11-2004');
    $burning_crusade = new \DateTime('16-01-2007');
    $wrath_of_the_lich_king = new \DateTime('13-11-2008');
    $cataclysm = new \DateTime('07-12-2010');
    $mists_of_pandaria = new \DateTime('25-09-2012');
    $warlords_of_draenor = new \DateTime('13-11-2014');
    $legion = new \DateTime('30-08-2016');

    // Content created date
    $created = new \DateTime();
    $created->setTimestamp($value);

    switch ($created) {
      case $created > $vanilla && $created < $burning_crusade:
//        echo(PHP_EOL . 'Vanilla');
        return 32;
      case $created > $burning_crusade && $created < $wrath_of_the_lich_king:
//        echo(PHP_EOL . 'Burning Crusade');
        return 94;
      case $created > $wrath_of_the_lich_king && $created < $cataclysm:
//        echo(PHP_EOL . 'Wrath of the Lich King');
        return 76;
      case $created > $cataclysm && $created < $mists_of_pandaria:
//        echo(PHP_EOL . 'Cataclysm');
        return 110;
      case $created > $mists_of_pandaria && $created < $warlords_of_draenor:
//        echo(PHP_EOL . 'Mists of Pandaria');
        return 111;
      case $created > $warlords_of_draenor && $created < $legion:
//        echo(PHP_EOL . 'Warlords of Draenor');
        return 112;
      case $created > $legion:
//        echo(PHP_EOL . 'Legion');
        return 113;
      default:
//        echo(PHP_EOL . 'Vanilla');
        return 32;
    }
  }
}
