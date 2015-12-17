# Downfall Redesign and Migration

A Migrate and Features implementation to pull content and structure for Drupal 6 downfallguild.org to a clean Drupal 8 site. A full redesign is involved.

Full details here: https://github.com/illepic/downfall-guild/wiki

## Quick Start

### Local Environment Requirements

* Vagrant
* Vagrant plugins
  * vagrant-hostsupdater: `vagrant plugin install vagrant-hostsupdater`
  * vagrant-vbguest: `vagrant plugin install vagrant-vbguest`
* VirtualBox
* Git

Windows-specific:
* [Symlinks enabled for Windows](http://blog.puphpet.com/blog/2015/06/25/windows-symlinks/)
* (Optional) [Cmder](http://cmder.net/) running as administrator
* (Optional) [HeidiSQL](http://www.heidisql.com/) for GUI database access

OSX-specific
* [SequelPro](http://www.sequelpro.com/) for GUI database access

## Initial

* Clone Druapl VM into our repo:

```shell
git clone git@github.com:geerlingguy/drupal-vm.git
```
    
* Copy settings from config to the VM:

```shell
cp config/config.yml drupal-vm
cp config/drupal.make.yml drupal-vm
```
    
* Turn the dev environment on and go make a sandwich. You may need to run this command as admin on Windows.
    
```shell
cd drupal-vm && vagrant up
```
    
* To Enter the dev environment:

```shell
cd drupal-vm && vagrant ssh
```

    
* Everything under `project/` in your local shows at `/var/www/df` in the VirtualBox
* (coming soon) Install tools: `npm install`. Only need to run this once.

### Initializing Local D6 (coming soon)
  
* Run `gulp d6:init`
* Install a recent d6 database via ssh db connection:
  * User `illepic_downfall`, pasword (lookup from live site)
  * Host 127.0.0.1, port 3306, database: illepic_downfall
  * SSH tunnel: direct.downfallguild.org, illepic, private key used

### Initializing Local D8 (coming soon)

* Run `gulp d8:init` (coming soon)
