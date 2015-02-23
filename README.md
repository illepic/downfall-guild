# Downfall Redesign and Migration

A Migrate and Features implementation to pull content and structure for Drupal 6 downfallguild.org to a clean Drupal 7 site. A full redesign is involved.

Full details here: https://github.com/illepic/downfall-guild/wiki

## Quick Start

### Install local

* Vagrant
  * vagrant-hostmanager: `vagrant plugin install vagrant-hostmanager`
  * vagrant-bindfs: `vagrant plugin install vagrant-bindfs`
* VirtualBox
* Git

## Initial

* Turn the dev environment on: `vagrant up`
  * If change in puphpet/config.yml, then after `vagrant up` run `vagrant provision`
* Enter the dev environment: `vagrant ssh`
* Go to the mapped working directory: `cd /var/www`
  * Everything under `project/` in your local shows at `/var/www` in the VirtualBox
  * Install tools: `npm install`. Only need to run this once.
  * Run `grunt d7:watch` for grunt to watch files changed in `project/build` and copy them to `project/web`