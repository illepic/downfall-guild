#!/usr/bin/env bash

# Symlink `config.yml` and `drupal.make.yml` from `config/` into `drupal-vm/`
cd drupal-vm && ln -sf ../config/config.yml && ln -sf ../config/drupal.composer.json

# Move back to root of repo
cd ../

# DELETE the D8 folder and kick off Vagrant.
sudo rm -rf project/web/d8 && cd drupal-vm && vagrant provision

# Back to root
cd ../

# Symlinks
bash ./project/scripts/symlinks.sh

# We don't want to rebuild d6 every time
#bash ./project/scripts/d6.sh
