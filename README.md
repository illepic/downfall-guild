# Downfall Redesign and Migration

A Migrate and Features implementation to pull content and structure for Drupal 6 downfallguild.org to a clean Drupal 7 site. A full redesign is involved.

Full details here: https://github.com/illepic/downfall-guild/wiki

## Repository Explanation

This repository uses git subtrees to pull in a number of different projects into their own folders. As such, committing, pulling, and pushing is a little different. 

## Prerequisite tools required

1. Ruby - available on all Macs
2. Bundler gem: `[sudo] gem install bundler`
3. PHP - should already be available in OSX

NOTE: We do NOT need Apache, or a local server for design. Pattern Lab helps us out here.

## Getting started - DESIGN

We are using Pattern Lab for our initial component design. The folder for Pattern Lab is at __redesign/patternlab__. 

1. Change directory to __redesign/patternlab/__ and run `php core/builder.php -wr`. Pattern Lab has started up a local server and is watching our project
2. In a web browser, open __redesign/patternlab/public/index.html__. Pattern Lab will refresh this page as we work.
3. Change directory to __redesign/patternlab/source/css__ and run `bundle install`. Bundler has now made sure that you are using correct versions of Sass and Compass
4. In a _new_ terminal window at this directory, run `[sudo] compass watch`. NOTE: You may need the sudo command here since we're using a beta version of Sass/Compass. ALSO NOTE: There _will_ be errors in your terminal. This is OK: Foundation is using some outdated methods that will be going away in Sass soon, newer Sass just lets us know.

## Workflow

We are using component based design and development. That means that every "pattern" is pretty self-contained. Our workflow is simple:

1. Make a mustache file that fits one of the Pattern Lab concepts: atoms, molecules, organisms, templates, or pages.
2. Write the Sass for that file within __redesign/patternlab/source/css/scss__

## Folder structure

* redesign
  * patternlab - Holds our patternlab files
    * foundation - All foundation files. We do _NOT_ edit these files.
    * source - This is where we edit mustache and Sass files
    * public - The rendered output from our work in source. These get blown away on every save.
