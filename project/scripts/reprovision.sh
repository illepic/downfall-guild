#!/usr/bin/env bash

# Reinstall drupal via drupalvm
bash ./project/scripts/drupalvm.sh

# Symlinks
bash ./project/scripts/symlinks.sh

#sudo bash -c 'cat project/build/dev/d8/sites/default/enable_local_settings.txt >> project/web/d8/web/sites/default/settings.php'

# Permissions needed for import/moving around files
chmod -R 777 project/web/d8/web/sites/default && chmod -R 777 project/web/d8/web/sites/default/*

# We don't want to rebuild d6 every time on provision
#bash ./project/scripts/d6.sh
