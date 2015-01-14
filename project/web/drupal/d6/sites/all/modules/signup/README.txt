$Id: README.txt,v 1.11 2007/12/11 09:56:55 dww Exp $

The signup module allows users to sign up for nodes of any type.  For
each signup-enabled node, this module provides options for sending a
notification email to a selected email address upon a new user signup
(good for notifying event coordinators, etc.), and a confirmation
email to users who sign up.  When used on event-enabled nodes (with
the event.module installed), it can also send out reminder emails to
all signups X days before the start of the event (per node setting),
and automatically close event signups X hours before their start
(general setting).  Settings exist for restricting signups to selected
roles and content types.

Support exists for both registered and anonymous users to sign up for
events.  Both can receive confirmation and reminder emails, and
registered users are also able to cancel their signups and view listings
of their current signups.

Conflict resolution features for registered users is also available by
enabling the signup_conflicts module, located in the contrib folder of the
signup module.

For installation instructions, see INSTALL.txt.

For instructions on upgrading, see UPGRADE.txt.

Send feature requests and bug reports to the issue tracking system for
the signup module: http://drupal.org/node/add/project_issue/signup.
For a list of future work, also see http://groups.drupal.org/node/5044.

This module was originally co-developed by Chad Phillips and Jeff
Robbins, and sponsored by Jeff Robbins.  It is now being maintained
by: Derek Wright (http://drupal.org/user/46549) a.k.a. "dww".
