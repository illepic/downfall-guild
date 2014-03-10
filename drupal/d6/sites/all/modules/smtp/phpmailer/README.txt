/* $Id: README.txt,v 1.4 2009/06/10 13:36:54 smk Exp $ */

-- SUMMARY --

Adds SMTP support for sending e-mails using the PHPMailer library.

For a full description of the module, visit the project page:
  http://drupal.org/project/phpmailer
To submit bug reports and feature suggestions, or to track changes:
  http://drupal.org/project/issues/phpmailer


-- REQUIREMENTS --

* PHPMailer for PHP5/6
  http://phpmailer.codeworxtech.com

Optional:

* Mime Mail module to send HTML e-mails
  http://drupal.org/project/mimemail

* Personalized E-mails module to adjust the displayed sender name
  http://drupal.org/project/pmail


-- INSTALLATION --

1. Download PHPMailer for PHP5/6 from

     http://sourceforge.net/project/showfiles.php?group_id=26031&package_id=252700

   and extract the the following files to the subdirectory 'phpmailer' of this
   module:

     class.phpmailer.php
     class.smtp.php
 
   Be careful NOT to extract the path names contained in the archive.

2. Install as usual, see http://drupal.org/node/70151 for further information.


-- CONFIGURATION --

When not using the optional Mime Mail module, customize module settings at
Administer >> Site configuration >> PHPMailer.

Otherwise PHPMailer will show up as an e-mail engine

To send e-mails with Google Mail use the following settings:

* SMTP server:     smtp.gmail.com
* SMTP port:       465
* Secure protocol: SSL
* Username:        <your google mail name>@gmail.com
* Password:        <your google mail password>

Note however, that Google automatically rewrites the "from" line of any e-mail
you send via their SMTP gateway to your Gmail address.


-- CREDITS --

Authors:
* Stefan M. Kudwien (smk-ka) - http://drupal.org/user/48898
* Daniel F. Kudwien (sun) - http://drupal.org/user/54136

This project has been sponsored by UNLEASHED MIND
Specialized in consulting and planning of Drupal powered sites, UNLEASHED
MIND offers installation, development, theming, customization, and hosting
to get you started. Visit http://www.unleashedmind.com for more information.

