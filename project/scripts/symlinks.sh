#!/usr/bin/env bash

pwd
# Symlink our customizations
cd project/web/d8/web/modules
ln -sf ../../../../build/dev/d8/modules/custom
cd ../themes
ln -sf ../../../../build/dev/d8/themes/custom
cd ../sites/default/files
ln -sf ../../../../../../build/dev/d8/sync

cd ../sites/default
sudo ln -sf ../../../../../build/dev/d8/sites/default/settings.local.php

# Back to root of project
cd ../../../../../../../
