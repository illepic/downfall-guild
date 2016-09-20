#!/usr/bin/env bash

# drush dump site up on webfaction
echo "You may be asked for the WebFaction password here. drush archive-dump is running up on WebFaction. Get comfy, this will take a LONG time!"
ssh illepic@direct.illepic.com "cd webapps/downfall_drupal/sites/www.downfallguild.org && drush -v archive-dump www.downfallguild.org --destination=/home/illepic/dfmigrate/df.tar.gz --overwrite && exit"

# Pull down d6 site
echo "Pulling down D6 site archive locally!"
rsync -zvrP illepic@direct.illepic.com:dfmigrate/ project/dfmigrate/

# cd to drupal-vm
cd drupal-vm

# Run vm script within vm
vagrant ssh --command "bash /var/www/df/scripts/vm/restore_d6.sh"

# cd back to root
cd ../
