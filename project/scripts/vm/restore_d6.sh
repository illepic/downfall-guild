#!/usr/bin/env bash

# RUN FROM WITHIN VAGRANT
cd /var/www/df

# `drush archive-restore` the entire site from within the Vagrant box. This will take a long time
echo "Go make a sandwich, this is going to take awhile."
drush -v archive-restore dfmigrate/df.tar.gz --destination=web/d6 --db-url=mysql://dfdbuser:dfdbpass@localhost/downfall_d6 --db-prefix=demo_ --overwrite

# Copy over d6 settings
cp -R build/dev/d6 web/d6
