#!/usr/bin/env bash

# cd to drupal-vm
cd drupal-vm
# Run vm script within vm
vagrant ssh --command "cd /var/www/df/web/d8/web/ && drush ms && drush mr upgrade_d6_$1 && drush cdi1 modules/custom/df_migration/config/install/migrate_plus.migration.upgrade_d6_$1.yml && drupal cr all && drush mi upgrade_d6_$1 && drush ms"

# cd back to root
cd ../
