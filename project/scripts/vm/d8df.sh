#!/usr/bin/env bash

# Get the D8 site installed and configured
cd /var/www/df/web/d8/web

chmod 777 sites/default/settings.php
drush si config_installer --account-name=admin --account-pass=admin -y
