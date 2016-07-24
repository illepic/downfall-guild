#!/usr/bin/env bash

cd drupal-vm

# Symlink `config.yml` and `drupal.make.yml` from `config/` into `drupal-vm/`
ln -sf ../config/config.yml
ln -sf ../config/drupal.composer.json

# Move back to root of repo
cd ../

# DELETE the D8 folder and kick off Vagrant.
sudo rm -rf project/web/d8
cd drupal-vm
vagrant provision

# Back to root
cd ../

# Symlinks
bash ./project/scripts/symlinks.sh

# Copy config
mkdir -p ./project/web/d8/web/sites/default/files/sync
cp ./project/build/dev/d8/modules/custom/df_config/sync/* ./project/web/d8/web/sites/default/files/sync/

# Permissions needed for import/moving around files
chmod -R 777 project/web/d8/web/sites/default && chmod -R 777 project/web/d8/web/sites/default/*

# We don't want to rebuild d6 every time on provision
#bash ./project/scripts/d6.sh
