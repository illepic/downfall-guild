# Downfall Redesign and Migration

A Migrate and Features implementation to pull content and structure for Drupal 6 downfallguild.org to a clean Drupal 8 site. A full redesign is involved.

Full details here: https://github.com/illepic/downfall-guild/wiki

## Quick Start

### Local Environment

* Vagrant
* Vagrant plugins
  * vagrant-hostmanager: `vagrant plugin install vagrant-hostmanager`
  * vagrant-vbguest: `vagrant plugin install vagrant-vbguest`
* VirtualBox
* Git

Windows-specific:
* [PowerShell](https://www.microsoft.com/en-us/download/details.aspx?id=40855)? (maybe)
* [Cmder](http://cmder.net/) running as administrator
* [Symlinks enabled for Windows](http://cmder.net/)
* [HeidiSQL](http://www.heidisql.com/) for GUI database access

OSX-specific
* [SequelPro](http://www.sequelpro.com/) for GUI database access

## Initial

* Turn the dev environment on: Run `vagrant up` from the **env** folder
  * If there is a change in puphpet/config.yml, then after `vagrant up` run `vagrant provision`
* Enter the dev environment: `vagrant ssh`
* Go to the mapped working directory: `cd /var/www/df`
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