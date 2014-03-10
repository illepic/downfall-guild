
Copyright 2005-2008 Khalid Baheyeldin (http://2bits.com)
Copyright 2008      Joao Ventura      (http://www.venturas.org)

Description
-----------
This module provides web site admins the factility to display Google AdSense
ads on their web site, thus earning revenue.


Resources
---------
You can read the module author's collection of articles on resources for
using Google Adsense with Drupal. They contain hints and tips on how to use
the module, as well as Adsense in general.

http://baheyeldin.com/click/476/0


Prerequisites
-------------
You must signup for a Google AdSense account.


Installation
------------
To install, copy the adsense directory and all its contents to your modules
directory.


Configuration
-------------
To enable this module, visit Administer -> Site building -> Modules, and
enable adsense, and one of the other modules in the Adsense group. The modules
marked as '(old)' are not using the new 'Managed Ads' feature of Google
AdSense, so you should only use them if you have ads in the old format or if
you know what you're doing.

To configure it, go to Administer -> Site configuration -> AdSense.

Follow the online instructions on that page on how to display ads and the
various ways to do so.


API
---
The adsense module provides developers with an API that can be used to control
the Adsense Client ID used for the particular page view.

You can decide to select a different Adsense Client ID based on the content
type, the user's role, the level of user points, the taxonomy of content page,
connecting to Google's API, or anything else imaginable.

To do so, your module must implement a hook called 'adsense', as follows:

Assuming your module is called: your_module.module, you must have the
following function in it. The function has an $op argument that you
should check:

function your_module_adsense($op, $args = array()) {
  static $client_id = NULL;

  switch ($op) {
    case 'settings':
        return array(
          'name' => 'Module name',
          'desc' => 'Anything about your module',
        );
      break;
    case 'client_id':
      if (!$client_id) {
        // We cache the client ID on this page load, to make sure all of the
        // client IDs on one page are the same
        // Here you can use whatever logic you want to select a Google
        // Adsense client ID. 
        // If the args parameter is not NULL, a format specific slot ID + 
        // Publisher ID needs to be returned in an array with 'slot' and
        // 'client' fields.
        // If the args parameter is NULL, return only the Publisher ID as a
        // string.
        $client_id = your_logic($args);
      }

      return $client_id;
  }
}

Your module's settings form must be of type MENU_LOCAL_TASK and located in
'admin/settings/adsense/publisher/your_module'.

After you install the module, it should appear on the adsense module settings
page, along with other modules. You should be able to select it, and configure
it.


Bugs/Features/Patches
---------------------
If you want to report bugs, feature requests, or submit a patch, please do
so at the project page on the Drupal web site.
http://drupal.org/project/adsense


Authors
-------
Khalid Baheyeldin (http://baheyeldin.com/khalid and http://2bits.com)
Joao Ventura      (http://venturas.org)

If you use this module, find it useful, and want to send the authors a thank
you note, then use the Feedback/Contact page at the URLs above.

The authors can also be contacted for paid customizations of this and other
modules.
