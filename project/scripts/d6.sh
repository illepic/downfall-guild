#!/usr/bin/env bash

# Pull down d6 site
rsync -zvrP illepic@direct.illepic.com:dfmigrate/ project/dfmigrate/

# cd to drupal-vm
cd drupal-vm

# Run vm script within vm
vagrant ssh --command "bash /var/www/df/scripts/vm/restore_d6.sh"

# cd back to root
cd ../
