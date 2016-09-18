#!/usr/bin/env bash

# Assuming starting from root

cd drupal-vm
git checkout tags/3.1.2 # Change me to update

# Symlink `config.yml` and `drupal.make.yml` from `config/` into `drupal-vm/`
ln -sf ../config/config.yml
ln -sf ../config/drupal.composer.json

# DELETE the D8 folder and kick off Vagrant.
sudo rm -rf ../project/web/d8
vagrant halt
vagrant up --provision

# Back to root
cd ../
