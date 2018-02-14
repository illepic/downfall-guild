<?php


$databases['migrate']['default'] = [
  'database' => 'migrate',
  'username' => 'root',
  'password' => 'root',
  'host' => 'localhost',
  'port' => '3306',
  'namespace' => 'Drupal\\Core\\Database\\Driver\\mysql',
  'driver' => 'mysql',
  'prefix' => 'demo_',
];

$config_directories[CONFIG_SYNC_DIRECTORY] = 'sites/default/files/sync';
