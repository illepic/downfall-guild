# Downfall Redesign and Migration

A migration and design overhaul of downfallguild.org. Content and structure from the live Drupal 6 version of downfallguild.org will be migrated into a newly redesigned Drupal 8 site.

[![Build Status](https://travis-ci.org/illepic/downfall-guild.svg?branch=master)](https://travis-ci.org/illepic/downfall-guild)

## The Project

The goals of this project are as follows:

* Install Drupal 8 locally
* Backup the production Drupal 6 site locally (files and database)
* Migrate files and data from the local Drupal 6 to the local Drupal 8
* Build out the features/config of the Drupal 8 site
* Local development of the Pattern Lab/Drupal theme

## Local Host Environment Requirements

* PHP 7.1
* MySQL 5.6
* [Git](https://git-scm.com/downloads)
* [Node v8](https://nodejs.org/en/download/)

### Recommended Tools

* Database GUI
  * Mac: [SequelPro](http://www.sequelpro.com/)
  * Linux/Windows: [MySQL Workbench](https://www.mysql.com/products/workbench/)

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

* Group node (Post): edit/view/create/delete is ONLY about that intermediary relationship entity
* Post: edit/view/create/delete is full node privvies

# 2018 Updates

## From scratch:

**All command run from folder also containing `composer.json`.**

Run dependency installation:

```bash
composer install
```

Make two databases, `downfall_d8` and `migrate`:

```bash
composer dfmigrate:databases_create
```

Install D8:

```bash
composer dfmigrate:install_d8
```

Add `migrate` db to D8 settings:

```bash
chmod 777 web/sites/default/settings.php && \
vendor/bin/drupal database:add --database=migrate --username=root --password=root --prefix=demo_ --host=localhost --driver=mysql --port=3306 && \
chmod 555 web/sites/default/settings.php
```

## Initialize: D6

Pull down all files from the D6 site and restore the database locally. Ensure the CloudFlare DNS settings have opened the `direct.downfallguild.org` entry.

1. `ssh` into webfaction and archive-dump the whole site. Run the following from root of repo:

    ```bash
    ssh USERNAME@direct.downfallguild.org
    cd webapps/downfall_d6/sites/www.downfallguild.org
    drush -v archive-dump www.downfallguild.org --destination=/home/illepic/dfmigrate/df.tar.gz --overwrite
    exit
    ```

2. `rsync` down the dfmigrate folder from webfaction. Run the following from root of repo:

    ```bash
    rsync -zvrP USERNAME@direct.downfallguild.org:dfmigrate/ import/
    ```

    Or simply grab a provided archive from Dropbox and restore it to `import/` so that the path to the archive is `import/df.tar.gz`

3. Extract archive. Run from root of project:

    ```bash
    tar -xvzf import/df.tar.gz -C import/
    ```

4. Import the d6 database. Run from sibling to composer.json:

    ```bash
    vendor/bin/drush sql-cli --db-url="mysql://root:root@127.0.0.1/migrate" < ../import/downfall_d6.sql
    ```

4. Copy over our local d6.local.downfallguild.org site settings file. Run the following from the root of the repo  (see: `start.sh`):

        echo "Are you at the root of the repo right now?"
        cp -R config/d6/ project/web/d6
