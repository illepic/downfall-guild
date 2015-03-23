# Downfall Redesign and Migration

A Migrate and Features implementation to pull content and structure for Drupal 6 downfallguild.org to a clean Drupal 7 site. A full redesign is involved.

Full details here: https://github.com/illepic/downfall-guild/wiki

## Quick Start

### Local Environment

* Vagrant
  * vagrant-hostmanager: `vagrant plugin install vagrant-hostmanager`
  * vagrant-bindfs: `vagrant plugin install vagrant-bindfs`
* VirtualBox
* Git

## Initial

* Turn the dev environment on: `vagrant up`
  * If there is a change in puphpet/config.yml, then after `vagrant up` run `vagrant provision`
* Enter the dev environment: `vagrant ssh`
* Go to the mapped working directory: `cd /var/www`
  * Everything under `project/` in your local shows at `/var/www` in the VirtualBox
  * Install tools: `npm install`. Only need to run this once.

### Initializing Local D6
  
* Run `gulp d6:init`
* Install a recent d6 database (details soon)

### Initializing Local D7

* Run `gulp d7:init` (only need to do this once)
* Run `gulp d7:watch` for grunt to watch files changed in `project/build` and copy them to `project/web`
* To kick off migration, run `drush mi --group="DownfallD2DMigration" --feedback="100 items"
* After migration is finished, enable the forum_access module, then run Node Access Permissions (/admin/reports/status/rebuild)