# Downfall Redesign and Migration

A Migrate and Features implementation to pull content and structure for Drupal 6 downfallguild.org to a clean Drupal 8 site. A full redesign is involved.

Full details here: https://github.com/illepic/downfall-guild/wiki

## Local Host Environment Requirements

* [VirtualBox](https://www.virtualbox.org/wiki/Downloads)
* [Vagrant](https://www.vagrantup.com/downloads.html)
  * Install Vagrant plugin: vagrant-hostsupdater: `vagrant plugin install vagrant-hostsupdater`
  * Install Vagrant plugin: vagrant-cachier: `vagrant plugin install vagrant-cachier`
* [https://git-scm.com/downloads](Git)
* [Node >= 4.2.3/NPM >= 2.14.7](https://nodejs.org/en/download/)
  * Install gulp globally and install all project packages: `npm install gulp -g && npm install`
* [https://docs.ansible.com/ansible/intro_installation.html](Ansible)
  * OSX: `brew install ansible`, Ubuntu: `sudo apt install ansible`, Windows: LOL

### Windows-specific:

WARNING: As of 2016/01/01 this box is simply not working on Windows. Will investigate further at a later date.

* [Symlinks enabled for Windows](http://blog.puphpet.com/blog/2015/06/25/windows-symlinks/)
* (Optional) [Cmder](http://cmder.net/) running as administrator
* (Optional) [HeidiSQL](http://www.heidisql.com/) for GUI database access

### OSX-specific

* [SequelPro](http://www.sequelpro.com/) for GUI database access

### Ubuntu-specific

* `sudo apt install nfs-common nfs-kernel-server`

All commands listed are assumed to be run from the root of the project unless otherwise noted.

## Initialize: D8 + VM

To initialize the project, from the root of the project run (warning, takes a long time):

    bash ./project/scripts/start.sh

To reset and build D8 again, run from root of project:

    bash ./project/scripts/reprovision.sh

This will attempt to run the following:


Clone the drupal-vm repo into the root of our project if it does not exist already. Run from root of repo:

````shell
git clone git@github.com:geerlingguy/drupal-vm.git && bash ./project/scripts/start.sh
````

Symlink `config.yml` and `drupal.make.yml` from `config/` into `drupal-vm/`. Run from root of repo:

````shell
cd drupal-vm && ln -sf ../config/config.yml && ln -sf ../config/drupal.composer.json
````

DELETE the D8 folder and kick off Vagrant. Run from root of folder (you'll need to `cd ..` if you just ran the prior command):

````shell
sudo rm -rf project/web/d8 && cd drupal-vm && vagrant provision
````

Symlink our customizations. Run from root of repo:

````shell
cd project/web/d8/web/modules && ln -sf ../../../../build/dev/d8/modules/custom && cd ../sites/default && sudo ln -sf ../../../../../build/dev/d8/sites/default/settings.local.php && sudo bash -c 'cat ../../../../../config/enable_local_settings.txt >> settings.php'
````

Ensure this line is **uncommented** in `project/web/d8/sites/default/settings.php`:

````php
if (file_exists(__DIR__ . '/settings.local.php')) {
  include __DIR__ . '/settings.local.php';
}
````

If vagrant did not already add these entries to your hosts file, add the following to `\Windows\System32\drivers\etc\hosts` on Windows or `/etc/hosts` on OSX/Linux:

````text
192.168.88.88  d8.local.downfallguild.org
192.168.88.88  d6.local.downfallguild.org
192.168.88.88  adminer.local.downfallguild.org
````

Enable our modules by ssh'ing into the Vagrant box first. Run from root of repo:

````shell
cd drupal-vm && vagrant ssh
cd /var/www/df/web/d8/web
drupal module:install df_migration
drupal config:import

OR, if we need everything and it wasn't enabled on a fresh provision (ie you've run drush site-install to blow everything away and start over):

drupal module:install df_migration
````

Rollback stuck migration:

````shell
drush php-eval 'var_dump(Drupal::keyValue("migrate_status")->set('your_migration_name', 0))'
````

Helpful wipe-out-and-start-over command

````shell
drush sql-query "TRUNCATE migrate_map_upgrade_d6_node_guild_app" && drush mr upgrade_d6_node_guild_app && drush cdi1 modules/custom/df_migration/config/install/migrate_plus.migration.upgrade_d6_node_guild_app.yml && drupal cr all && drush mi upgrade_d6_node_guild_app --idlist="12331"
````

### Drupal 8

Drupal 8 is built completely from scratch if and only if the `project/web/d8` folder does not exist.

## Vagrant:

Enter the Vagrant box:

```shell
cd drupal-vm && vagrant ssh
```

Everything under `project/` in your local shows at `/var/www/df` in the VirtualBox

Halt the Vagrant box by `cd drupal-vm && vagrant halt`. Halting is highly recommended while not actively working on the project and very much recommended before shutting down your OS.

A Vagrant box can be started right up from where you left off with `cd drupal-vm && vagrant up`. This is the recommended way to come back to work on the project.

#### Nuke it

Sometimes Vagrant gets REALLY stuck. In these cases, the following steps will allow you to rebuild again. Run from root of repo:

1. `cd drupal-vm && vagrant destroy -f`
2. Open Virtualbox, find the **downfall.dev** box, right click and Remove all including files.

## Initialize: D6

To pull down all files from the D6 site and restore the database locally:

1. `ssh` into webfaction and archive-dump the whole site. Run the following from root of repo:

    ```shell
    ssh USERNAME@direct.illepic.com
    cd webapps/downfall_drupal/sites/www.downfallguild.org
    drush -v archive-dump www.downfallguild.org --destination=/home/illepic/dfmigrate/df.tar.gz --overwrite
    exit
    ```

2. `rsync` down the dfmigrate folder from webfaction. Run the following from root of repo:

    ```shell
    rsync -zvrP USERNAME@direct.illepic.com:dfmigrate/ project/dfmigrate/
    ```

Or simply grab a provided archive from Dropbox and restore it to `project/dfmigrate` so that the path to the archive is `project/dfmigrate/df.tar.gz`

3. `drush archive-restore` the entire site from within the Vagrant box. This will take a long time. Run the following **from the root of the repo**:

    ```shell
    cd drupal-vm
    vagrant ssh
    cd /var/www/df
    echo "Go make coffee. This is going to take awhile."
    drush -v archive-restore dfmigrate/df.tar.gz --destination=web/d6 --db-url=mysql://dfdbuser:dfdbpass@localhost/downfall_d6 --db-prefix=demo_ --overwrite
    exit
    ```

4. Copy over our local d6.local.downfallguild.org site settings file. Run the following from the root of the repo:

    ```shell
    echo "Are you at the root of the repo right now?"
    cp -R config/d6/ project/web/d6
    ```

## Migration to Drupal 8

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


    
## Prototyping redesign
