# Downfall Redesign and Migration

A Migrate and Features implementation to pull content and structure for Drupal 6 downfallguild.org to a clean Drupal 7 site. A full redesign is involved.

Full details here: https://github.com/illepic/downfall-guild/wiki

## Quick Start

### Install

* Vagrant
  * vagrant-hostmanager: `vagrant plugin install vagrant-hostmanager`
  * vagrant-bindfs: `vagrant plugin install vagrant-bindfs`
* VirtualBox

## Migration

* `vagrant up`
  * If change in puphpet/config.yml, then after `vagrant up` run `vagrant provision`
* `vagrant ssh`
* cd /var/www
* `drush make make/d7-generate.make test --no-core`