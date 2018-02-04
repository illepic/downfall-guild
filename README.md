# Downfall Redesign and Migration

A migration and design overhaul of downfallguild.org. Content and structure from the live Drupal 6 version of downfallguild.org will be migrated into a newly redesigned Drupal 8 site.

[![Build Status](https://travis-ci.org/illepic/downfall-guild.svg?branch=master)](https://travis-ci.org/illepic/downfall-guild)

## The Project

The goals of this project are as follows:

* Install Drupal 8 locally using Drupal VM (including all composer dependencies)
* Backup the production Drupal 6 site locally (files and database)
* Migrate files and data from the local Drupal 6 to the local Drupal 8
* Build out the features/config of the Drupal 8 site
* Local development of the Pattern Lab/Drupal theme

## Local Host Environment Requirements

* [VirtualBox 5](https://www.virtualbox.org/wiki/Downloads)
* [Vagrant 1.8](https://www.vagrantup.com/downloads.html)
	* Install Vagrant plugin: vagrant-hostsupdater: `vagrant plugin install vagrant-hostsupdater`
	* Install Vagrant plugin: vagrant-cachier: `vagrant plugin install vagrant-cachier`
* [Git](https://git-scm.com/downloads)
* [Node v6](https://nodejs.org/en/download/)
* [Ansible](https://docs.ansible.com/ansible/intro_installation.html)
	* OSX: `brew install ansible`
	* Ubuntu: `sudo apt install ansible`
	* Windows: LOL

I've given up supporting Windows on this project, maybe Windows 10 Bash can help?

### Ubuntu-specific

NFS filesystem makes syncing changes back and forth to Vagrant much faster:

	sudo apt install nfs-common nfs-kernel-server`

### Recommended Tools

* Database GUI
	* Mac: [SequelPro](http://www.sequelpro.com/)
	* Linux: [MySQL Workbench](https://www.mysql.com/products/workbench/)

## Getting started

To start fresh after a `git clone` of this project, run the following from the root of the project (warning, takes a long time):

    bash ./project/scripts/start.sh
    
This needs to be run at least once! This also depends on the remote D6 site having been backed up, which you can do by hand here (link here).

## Reprovision

It's often best to just restart while working locally. To reset and build D8 again, run from root of project:

    bash ./project/scripts/reprovision.sh

This should wipe out the D8 site, reprovision the VM, and install Drupal back to a fresh profile install.

## Things to ensure

Both of the Drupal VM config files ( `config.yml` and `drupal.make.yml`) must be symlinked from `config/` into `drupal-vm/`. 

Ensure this line is **uncommented** in `project/web/d8/sites/default/settings.php`:

````php
if (file_exists(__DIR__ . '/settings.local.php')) {
  include __DIR__ . '/settings.local.php';
}
````

If vagrant did not already add these entries to your hosts file, add the following to `/etc/hosts` on OSX/Linux:

````text
192.168.88.88  d8.local.downfallguild.org
192.168.88.88  d6.local.downfallguild.org
192.168.88.88  adminer.local.downfallguild.org
````

## Working in the Vagrant box

Jump into the Drupal 8 site by (from project root on host):

    cd drupal-vm && vagrant ssh
    
Everything under `project/` in your local shows at `/var/www/df` in the VirtualBox.

    cd /var/www/df/web/d8/web

Now all `drush` and `drupal` commands work. For instance:
	
	 # Migrate status
    drush ms
    # Install df_migration module
    drupal module:install df_migration
    # Import all config from sync directory
    drupal config:import

Site reinstall using our new install profile (from within Vagrant)

    cd /var/www/df/web/d8/web
    chmod 777 sites/default/settings.php
    drush si config_installer --account-name=admin --account-pass=admin

Sometimes Vagrant gets REALLY stuck. In these cases, the following steps will allow you to rebuild again. Run from root of repo:

1. `cd drupal-vm && vagrant destroy -f`
2. Open Virtualbox, find the **downfall.dev** box, right click and Remove all including files.

## Initialize: D6

To pull down all files from the D6 site and restore the database locally (this is done as part of `start.sh` script):

1. `ssh` into webfaction and archive-dump the whole site. Run the following from root of repo:

        ssh USERNAME@direct.downfallguild.org
        cd webapps/downfall_d6/sites/www.downfallguild.org
        drush -v archive-dump www.downfallguild.org --destination=/home/illepic/dfmigrate/df.tar.gz --overwrite
        exit

2. `rsync` down the dfmigrate folder from webfaction. Run the following from root of repo (see: `start.sh`):

        rsync -zvrP USERNAME@direct.downfallguild.org:dfmigrate/ project/dfmigrate/

    Or simply grab a provided archive from Dropbox and restore it to `project/dfmigrate` so that the path to the archive is `project/dfmigrate/df.tar.gz`

3. `drush archive-restore` the entire site from within the Vagrant box. This will take a long time. Run the following **from the root of the repo**  (see: `start.sh`):

        cd drupal-vm
        vagrant ssh
        cd /var/www/df
        echo "Go make coffee. This is going to take awhile."
        drush -v archive-restore dfmigrate/df.tar.gz --destination=web/d6 --db-url=mysql://dfdbuser:dfdbpass@localhost/downfall_d6 --db-prefix=demo_ --overwrite
        exit

4. Copy over our local d6.local.downfallguild.org site settings file. Run the following from the root of the repo  (see: `start.sh`):

        echo "Are you at the root of the repo right now?"
        cp -R config/d6/ project/web/d6

## Migration to Drupal 8 (clean up below)

Rollback stuck migration (in Vagrant):

    drush mrs your_migration_name

Helpful wipe-out-and-start-over command (in Vagrant):

    drush mr upgrade_d6_node_guild_app && drush cdi1 modules/custom/df_migration/config/install/migrate_plus.migration.upgrade_d6_node_guild_app.yml && drupal cr all && drush mi upgrade_d6_node_guild_app

See this article for most details: https://drupalize.me/blog/201605/custom-drupal-drupal-migrations-migrate-tools.

From root of project:

    cd drupal-vm && vagrant ssh
    cd /var/www/df/web/d8/web && drupal module:install df_migration
    # DO THIS MANUAL:

DOCUMENTATION PURPOSES ONLY, NO NEED TO RUN: This was already run, but to config export:

    drush migrate-upgrade --legacy-db-url="mysql://dfdbuser:dfdbpass@127.0.0.1/downfall_d6" --legacy-db-prefix="demo_" --legacy-root="http://d6.local.downfallguild.org" --configure-only

Run ALL the migrations:

    drush mi --feedback="100 items"

Run all dependencies up to a specific migration

    drush mi migration_name --execute-dependencies --feedback="100 items"

Migration tip: Rollback, reload config for migration, clear cache, run upgrade

    drush mr upgrade_d6_node_guild_app && drush cdi1 modules/custom/df_migration/config/install/migrate_plus.migration.upgrade_d6_node_guild_app.yml && drupal cr all && drush mi upgrade_d6_node_guild_app

Install to clean starting point:

    drupal module:install df_migration && drupal config:import --directory=modules/custom/df_config/sync && drupal config:import --directory=modules/df_groups/sync

## Prototyping redesign

## Groups

In regards to Group permissions:

- Group node (Post): edit/view/create/delete is ONLY about that intermediary relationship entity
- Post: edit/view/create/delete is full node privvies
