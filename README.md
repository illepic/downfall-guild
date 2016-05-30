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

Running this gulp task:

```shell
gulp d8:rebuild
```

attempts to run the following setup:

1. Clone the drupal-vm repo into the root of our project if it does not exist already
2. Update the drupal-vm repo in the root of our project if it does exist already
3. Copy `config.yml` and `drupal.make.yml` from `config/` into `drupal-vm/`
4. Kick off a full `vagrant halt && vagrant up` to build our Vagrant box dev environment
5. Build Drupal completely from the make file
6. Symlink all our custom modules into the Vagrant box from `project/build/dev/d8/modules/custom` to `web/d8/modules/custom` 

If vagrant did not already add these entries to your hosts file, add the following to `\Windows\System32\drivers\etc\hosts` on Windows or `/etc/hosts` on OSX/Linux:

````text
192.168.88.88  d8.local.downfallguild.org
192.168.88.88  d6.local.downfallguild.org
192.168.88.88  adminer.local.downfallguild.org
````

### Drupal 8

Drupal 8 is built completely from scratch if and only if the `project/web/d8` folder is **empty**.

* To rebuild Drupal, simpley delete the `project/web/d8/` folder and re-run `gulp d8:rebuild`
* Otherwise, running `gulp d8:rebuild` simply updates the `drupal-vm/` repo, halts Vagrant, and re-provisions it (leaving Drupal alone)

## Vagrant:

Enter the Vagrant box:

```shell
cd drupal-vm && vagrant ssh
```
    
Everything under `project/` in your local shows at `/var/www/df` in the VirtualBox

Halt the Vagrant box by `cd drupal-vm && vagrant halt`. Halting is highly recommended while not actively working on the project and very much recommended before shutting down your OS.

A Vagrant box can be started right up from where you left off with `cd drupal-vm && vagrant up`. This is the recommended way to come back to work on the project.

#### Nuke it

Sometimes Vagrant gets REALLY stuck. In these cases, the following steps will allow you to run `gulp d8:rebuild` again:

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

Ensure that `project/build/d8/sites/default/settings.local.php` is copied/symlinked to `project/web/d8/sites/default/settings.local.php`. Then, ensure this line is **uncommented** in `project/web/d8/sites/default/settings.local.php`:

    if (file_exists(__DIR__ . '/settings.local.php')) {
      include __DIR__ . '/settings.local.php';
    }

Run the following for config export (NOTE: This will have already been done and saved to the site module, this is here for documentation purposes):

    drush migrate-upgrade --legacy-db-url="mysql://dfdbuser:dfdbpass@127.0.0.1/downfall_d6" --legacy-db-prefix="demo_" --legacy-root="http://d6.local.downfallguild.org" --configure-only
    


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
