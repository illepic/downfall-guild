<?php


$databases['migrate']['default'] = array (
  'database' => 'downfall_d6',
  'username' => 'dfdbuser',
  'password' => 'dfdbpass',
  'prefix' => 'demo_',
  'host' => 'localhost',
  'port' => '3306',
  'namespace' => 'Drupal\\Core\\Database\\Driver\\mysql',
  'driver' => 'mysql',
);

$config_directories[CONFIG_SYNC_DIRECTORY] = 'sites/default/files/sync';
