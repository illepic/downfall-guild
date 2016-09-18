#!/usr/bin/env bash

pwd
echo "Symlinking now!" ;

# Symlink our customizations
cd project/web/d8/web/modules
ln -sf ../../../../build/dev/d8/modules/custom
cd ../themes
ln -sf ../../../../build/dev/d8/themes/custom
cd ../sites/default/files
ln -sf ../../../../../../build/dev/d8/sync

cd ../
sudo ln -sf ../../../../../build/dev/d8/sites/default/settings.local.php
sudo ln -sf ../../../../../build/dev/d8/sites/default/settings.php

# Back to root of project
cd ../../../../../../../
