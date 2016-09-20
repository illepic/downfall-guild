#!/usr/bin/env bash

# Reinstall drupal via drupalvm
bash ./project/scripts/drupalvm.sh

# Symlinks
bash ./project/scripts/symlinks.sh

#sudo bash -c 'cat project/build/dev/d8/sites/default/enable_local_settings.txt >> project/web/d8/web/sites/default/settings.php'

# Permissions needed for import/moving around files
chmod -R 777 project/web/d8/web/sites/default
chmod -R 777 project/web/d8/web/sites/default/*

# Get the D8 site installed and configured
cd drupal-vm/
vagrant ssh --command "bash /var/www/df/scripts/vm/d8df.sh"
cd ../
