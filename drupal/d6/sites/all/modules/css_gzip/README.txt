// $Id: README.txt,v 1.4.2.1 2009/09/02 23:48:42 mikeytown2 Exp $
CSS gzip module for Drupal 6
==================================

Installation
------------

 1) Copy the CSS gzip module to sites/all/modules.

 2) Enable it in admin/build/modules.

 3) Enable CSS Optimization in admin/settings/performance.

 4) Compress the CSS even more by enabling GZip compression.


Issues
------
If using a recolorable theme you might have to turn on "GZip CSS: Use hook exit as well."

Certian hosts do not like mutiple .htaccess files. To get around this issue you need to copy the text below into drupal's root .htaccess file, and enable the "GZip CSS: Do not generate .htaccess file" checkbox.
Add this Inside the <IfModule mod_rewrite.c> block, right before </IfModule> (add it to the bottom)

  ### START CSS GZIP ###
  # Requires mod_mime to be enabled.
  <IfModule mod_mime.c>
    # Send any files ending in .gz with x-gzip encoding in the header.
    AddEncoding gzip .gz
  </IfModule>
  # Gzip compressed css files are of the type 'text/css'.
  <FilesMatch "\.css\.gz$">
    ForceType text/css
  </FilesMatch>
  <IfModule mod_rewrite.c>
    RewriteEngine on
    # Serve gzip compressed css files
    RewriteCond %{HTTP:Accept-encoding} gzip
    RewriteCond %{REQUEST_FILENAME}\.gz -s
    RewriteRule ^(.*)\.css $1\.css\.gz [L,QSA,T=text/css]
  </IfModule>
  ### End CSS GZIP ###