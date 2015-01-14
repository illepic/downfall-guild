***********
* README: *
***********

DESCRIPTION:
------------
This module offers the possibility to add prefix and suffix 
values for each cck widget.


REQUIREMENTS:
-------------
The form_markup.module requires the content.module to be installed.


INSTALLATION:
-------------
1. Place the entire form_markup directory into your Drupal sites/all/modules/
   directory.

2. Enable the form_markup module by navigating to:

     administer > modules
     

USING FORM_MARKUP:
-----------------
When creating a new or editing an existing field, there a fieldset called Markup appears. 
Here you can set, what additional html markup will be added around your field. Both fields are
optional, so you can leave it empty or just fill in one or both. 

Examples:
  - add a div (e.g. to address your field in css):
      prefix: <div id="my-special-field">
      suffix: </div>
  - add a 'clearing' break when using floatings: 
      suffix: <span class="clear"></span> (or <br clear="all" /> )

Author:
-------
Matthias Hutterer
mh86@drupal.org
m_hutterer@hotmail.com
