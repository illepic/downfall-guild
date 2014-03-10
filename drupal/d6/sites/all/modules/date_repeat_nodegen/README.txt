Date Repeat Node Generator
==========================

This module is intended as an add-on for the wonderful Date Repeat module, part of the Date package of modules.  It grew
out of the feature request discussion at http://drupal.org/node/298334.

Date Repeat allows you to specify a wide range of repeating date sequences.  However, these sequences are all stored
within a single node, and merely presented as separate dates on calendars.  If you have a series of events which occur
periodically, but each event is different from the other - e.g., a weekly game where the opposing teams are different
each week - Date Repeat doesn't quite do what you need.

This module fixes that problem by allowing you to generate one node for each event in your sequence, upon creation of
the first node.  As part of the node editing form, you'll see a question prompting you to "Generate each date as a single node".
Answering no will stick with the default Date Repeat behavior.  Answering yes will ceate one node for each date in the
repeating pattern you've specified, as determined by the Date Repeat API.  (This behavior only occurs when you create a new
node; because sequence editing has not yet been tackled, nothing at all happens when you update an existing node.)

This module is not yet ready for a production site.  It only allows you to create a new sequence of nodes; other popular
date sequence features, like changing the pattern for all events in the sequence or all future events in the sequence upon edit,
are not yet supported.  There have been bugs reported which could not reproduced but might surface again, and in other ways
the module is a bit rough around the edges.  So don't use it on a production site, but by all means, test and submit patches
and feedback!