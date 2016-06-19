#!/usr/bin/env bash

pwd
# Symlink our customizations
cd project/web/d8/web/modules
ln -sf ../../../../build/dev/d8/modules/custom

cd ../sites/default
sudo ln -sf ../../../../../build/dev/d8/sites/default/settings.local.php
sudo bash -c 'cat ../../../../../build/dev/d8/sites/default/enable_local_settings.txt >> settings.php'
