# Downfall Redesign and Migration

A Migrate and Features implementation to pull content and structure for Drupal 6 downfallguild.org to a clean Drupal 8 site. A full redesign is involved.

Full details here: https://github.com/illepic/downfall-guild/wiki

## Local Environment Requirements

* [VirtualBox](https://www.virtualbox.org/wiki/Downloads)
* [Vagrant](https://www.vagrantup.com/downloads.html)
  * Install Vagrant plugin: vagrant-hostsupdater: `vagrant plugin install vagrant-hostsupdater`
* [https://git-scm.com/downloads](Git)
* [Node >= 4.2.3/NPM >= 2.14.7](https://nodejs.org/en/download/)
  * Install gulp globally and install all project packages: `npm install gulp -g && npm install`

Windows-specific:

WARNING: As of 2016/01/01 this box is simply not working on Windows

* [Symlinks enabled for Windows](http://blog.puphpet.com/blog/2015/06/25/windows-symlinks/)
* (Optional) [Cmder](http://cmder.net/) running as administrator
* (Optional) [HeidiSQL](http://www.heidisql.com/) for GUI database access

OSX-specific

* [SequelPro](http://www.sequelpro.com/) for GUI database access

Ubuntu-specific

* `sudo apt-get install nfs-common nfs-kernel-server`

All commands listed are assumed to be run from the root of the project unless otherwise noted.

## Initialize: D8 + VM

Clone the drupal-vm repo into the root of our project if it does not exist already. Run from root of repo:

````shell
git clone git@github.com:geerlingguy/drupal-vm.git
````

Symlink `config.yml` and `drupal.make.yml` from `config/` into `drupal-vm/`. Run from root of repo:

````shell
cd drupal-vm && ln -sf ../config/config.yml && ln -sf ../config/drupal.make.yml
````

DELETE the D8 folder and kick off Vagrant. Run from root of folder (you'll need to `cd ..` if you just ran the prior command):

````shell
sudo rm -rf project/web/d8 && cd drupal-vm && vagrant provision
````

Symlink our customizations. Run from root of repo:

````shell
cd project/web/d8/modules && ln -sf ../../../build/dev/d8/modules/custom && cd ../sites/default && sudo ln -sf ../../../../build/dev/d8/sites/default/settings.local.php && sudo bash -c 'cat ../../../../../config/enable_local_settings.txt >> settings.php'
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
cd /var/www/df/web/d8
drupal module:install df_config df_migration

OR, if we need everything and it wasn't enabled on a fresh provision (ie you've run drush site-install to blow everything away and start over):
drupal module:install devel migrate_upgrade migrate_plus migrate_tools migrate_manifest config_devel kint df_config df_migration
````

Rollback stuck migration:

````shell
drush php-eval 'var_dump(Drupal::keyValue("migrate_status")->set('your_migration_name', 0))'
````

### Drupal 8

Drupal 8 is built completely from scratch if and only if the `project/web/d8` folder does not exist.

* OBSOLETE: To rebuild Drupal, simpley delete the `project/web/d8/` folder and re-run `gulp d8:rebuild`
* OBSOLETE: Otherwise, running `gulp d8:rebuild` simply updates the `drupal-vm/` repo, halts Vagrant, and re-provisions it (leaving Drupal alone)

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
    cd /var/www/df/web/d8 && drupal module:install df_config df_migration

DOCUMENTATION PURPOSES ONLY, NO NEED TO RUN: This was already run, but to config export:

    drush migrate-upgrade --legacy-db-url="mysql://dfdbuser:dfdbpass@127.0.0.1/downfall_d6" --legacy-db-prefix="demo_" --legacy-root="http://d6.local.downfallguild.org" --configure-only

Notes:
  - Did all content with "upload" fields end up as Posts?
  - SOLVED: Need a simple map for formats, ie "If full_html, just use existing"
    - Everything just comes over as basic_html now, PERIOD.
  - SOLVED: Do we even need revisions? Test by commenting out all revision migrations to simplify
    - No revisions, not needed
  - SOLVED: Need content type called "Post" to map Forums, Blogs,
    - Now part of df_config module, provides a basic content type, comments field.
  - SOLVED: Blog/Forums fail to move to Post content type if they have an "upload"
  - img_assist process plugin should lookup in D8 db, file_managed table to get public file uri instead of d6 table doing the hard str_replace
  - On file import, ditch all thumbnail and gallery size entries
  - Need content type for image to understand the Image field
  - Failed (maybe run later?) upgrade_d6_field_instance, upgrade_d6_field_instance_widget_settings
    - Yeah, all fields failed to come over
    - We really don't want these though. We have the definitions if we **really** want them. We'll transform instead.

## Prototyping redesign

NOTE: Windows users: Install Visual Studio Community Edition 2015. Open it, create a Visual C++ project. You'll see an option to:

    "Install Visual C++ 2015 Tools for Windows Desktop"

Do the above, then run:

    npm install -g browser-sync --msvs_version=2015

The following sets up PatternLab for first use, should only be done once or when starting over:

```shell
cd redesign/pl && npm install
```
You may see an error on Windows regarding utf-8-validate not compiling. This doesn't affect us.

Temp: Run `cd redesign/pl && gulp` at least once to do an initial PL build.

Temp: Run `cd redesign/pl && gulp serve` to compile assets and refresh the prototype.
