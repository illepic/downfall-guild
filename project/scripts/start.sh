#!/usr/bin/env bash

# Clone drupal-vm
git clone git@github.com:geerlingguy/drupal-vm.git

# Repeatable provision process here
bash ./project/scripts/reprovision.sh

# Build d6
bash ./project/scripts/d6.sh
