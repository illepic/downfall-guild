About the Flexible theme
========================

This theme is designed with accessibility in mind.  Specific features are:
 - links at start of page to enable user to skip to relevant part of page
 - pre header region to give a little more flexibility to the header layout - ie items can be placed before or after the logo
 - Three-column layout: left and right sidebars and a central content area
 - access settings to allow users to select their preferred colours and fonts
 - implementation of standard access keys
 - ability to linearise the content
 - ability to customise on a site-specific basis

Screen layout
=============
id = access - Accessiblity links
id = accessibilityguide - Link to the site's accessibility guide (url = _access_)
class = layout - Layout table for page (see notes below in the use of a table!)
	id = header - Wrapper for the header elements
		id = pre-header - Drupal pre header region for elements placed before the logo
		id = title - Site title
		id = logo - Site logo
		id = site_name - Site name
		id = site_slogan - Site slogan
		id = header-region - Drupal header region for elements placed after the logo
	id = sidebar-left - Drupal left sidebar region
	id = content - Main content region
		class = breadcrumb - Drupal breadcrumb trail
		id = mission - Mission statement
		id = tabs-wrapper - Drupal menu tabs
			page title
			tabs
		help text
		messages
		content
		feed_icons
	id = sidebar-right - Drupal right sidebar region
	id = footer - Drupal footer region
		id = footer_wrapper
			Footer message
	id = accesssettings - Accessibility settings
		colour selector
		font selector
		link to access guide
		link to faq
		link to terms and conditions

Accessibility keys
=================
The following keys are implemented:
Access key 	Description 		Implemented
S 			Skip navigation 	Yes - skips to the main page content
1 			Home page 			Yes - takes you to the home page
2 			What's new 			Not implemented
3 			Site map 			Yes - skips to the navigation menu
4 			Search 				Yes - skips to the search box
5 			Frequently Asked Questions (F.A.Q.) 	
								Yes - takes you to the F.A.Q. page
6 			Help 				Yes - skips to the accessiblity settings
7 			Complaints procedure 	
								Not implemented
8 			Terms and conditions 	
								Yes - takes you to the Privacy Policy page
9 			Feedback form 		Not implemented
0 			Access key details 	Yes - takes you to the accessibility guide

Implementation
==============
For some of the features to work properly, you need to perform additional configuration on your site

 - The Path module needs to be enabled.  This will let you create specifically-named pages.
 
 - You need to create a page with an accessibility guide for your site.  This should be given the URL of _access_.
 
 - To enable the "Skip to navigation" feature you need to create a new Drupal block:
	- call it skip_n (for example, the exact name doesn't matter)
	- the block should contain the following html:
		<a id="skip_n"></a>
	- the block should be placed where it is most useful - ie immediately before the site navigation menu

 - To create an accessibility link to the site FAQ
	- the page's url should be _faq_
	- a link to the _faq_ page should be placed in the navigation menu

 - To create site Terms and conditions
	- the page's url should be _terms_
	- a link to the _terms_ page should be placed in the navigation menu

Stylesheets
===========
The theme has default stylesheets for layout, colour and fonts.  It also comes with alternative colour and font stylesheets, which can be selected by the user.

The three main sheets for the theme are:
 _default._default.css - default layout
 colour._default.css - default colours *
 font._default.css - default fonts *
 
 * these two are not strictly necessary, you can put all the defaults for layout, colour and font into _default._default.css
 
The theme also has alternative stylesheets for colour and font, eg:
 colour.high contrast.css
 font.large.css
 font.very large.css
 
These alternative stylesheets will be presented to the user as options at the foot of the screen.  They can select an alternative stylesheet and save their preference.

You can also create a subdirectory of the theme, which contains additional or replacement stylesheets.
 - If the name is the same as one in the main theme, the site-specific style sheet will override the theme, eg:
		site/_default._default.css will override the main theme default layout
		site/font.large.css will override the main theme large font alternative sheet
 - If the name is different:
	layout (_default...) stylesheets will be loaded in addition to the theme layout stylesheet, eg:
		site/_default.extra.css will be loaded in addition to _default._default.css
	colour and font stylesheets will be presented as additional options for the user to select, eg:
		site/font.tiny.css will give the user a further choice of font stylesheets
	
A word on layout tables
=======================
There seems to be a "received wisdom" that using <table> to lay out your pages is bad and you MUST use <div> tags, especially when designing accessible websites.  I have this to say on the matter.

I have looked at many many ways of getting divs to lay a page out properly and
 - they are all complex to some degree
 - cross-browser compatibility is a nightmare
 - they all break down as some point
 - they don't address the issue of accesibility as they don't behave in predictable ways when using alternative browsers
 
Laying out a 2 or 3-column page is one of the most common operations in web design and it should be easy to achieve.  It should not be necessary to use long-winded and imperfect methods to achieve something so fundamental and simple.  Only layout tables can do this

The solution built into this theme is simple.  By default it uses a layout table.  It works very well in all circumstances.  It's also compliant with W3C guidelines.  But, if the user chooses "linear layout" in the accessibility features, they can have the content delivered in <divs> - accessbility links let the user skip around the screen.

So, until HTML/CSS can do with divs what is so simple to do with tables, I will stick to tables.  But using the power of Drupal I will provide an alternative to those that want it.

