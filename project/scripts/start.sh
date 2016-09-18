#!/usr/bin/env bash

# Clone drupal-vm
git clone git@github.com:geerlingguy/drupal-vm.git

# Reinstall drupal via drupalvm
bash ./project/scripts/drupalvm.sh

# Symlinks
bash ./project/scripts/symlinks.sh

# Permissions needed for import/moving around files
chmod -R 777 project/web/d8/web/sites/default
chmod -R 777 project/web/d8/web/sites/default/*

# Build d6
bash ./project/scripts/d6.sh
