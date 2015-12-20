# Downfall Redesign and Migration

A Migrate and Features implementation to pull content and structure for Drupal 6 downfallguild.org to a clean Drupal 8 site. A full redesign is involved.

Full details here: https://github.com/illepic/downfall-guild/wiki

## Quick Start

### Local Environment Requirements

* [VirtualBox](https://www.virtualbox.org/wiki/Downloads)
* [Vagrant](https://www.vagrantup.com/downloads.html)
  * Install Vagrant plugin: vagrant-hostsupdater: `vagrant plugin install vagrant-hostsupdater`
* [https://git-scm.com/downloads](Git)
* [Node >= 4.2.3/NPM >= 2.14.7](https://nodejs.org/en/download/)
  * Install gulp globally and install all project packages: `npm install gulp -g && npm install`

Windows-specific:

* [Symlinks enabled for Windows](http://blog.puphpet.com/blog/2015/06/25/windows-symlinks/)
* [rsync for windows](http://codingsimply.com/blog/grunt-rsync-and-windows)
* (Optional) [Cmder](http://cmder.net/) running as administrator
* (Optional) [HeidiSQL](http://www.heidisql.com/) for GUI database access

OSX-specific

* [SequelPro](http://www.sequelpro.com/) for GUI database access

## Initial: D8

Running this gulp task:

```shell
gulp d8:rebuild
```

attempts to run following setup:

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

### Drupal

Drupal is built completely from scratch if and only if the `project/web/d8` folder is **empty**.

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

## Initial: D6
  
* Run `gulp d6:init --user=WEBFACTIONUSERNAME` to sync download the entire original Downfall site
* (Coming soon) Install a recent d6 database via ssh db connection:
  * User `illepic_downfall`, pasword (lookup from live site)
  * Host 127.0.0.1, port 3306, database: illepic_downfall
  * SSH tunnel: direct.downfallguild.org, illepic, private key used
