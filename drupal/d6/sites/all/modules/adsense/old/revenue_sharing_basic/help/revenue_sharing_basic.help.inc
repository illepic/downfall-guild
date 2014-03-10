<?php
// Copyright 2005-2008 Khalid Baheyeldin - http://2bits.com
// Copyright 2008 Joao Ventura - http://www.venturas.org

/**
 * @file
 * Helpfile for the revenue_sharing_basic module
 */

/**
 * Creates the help text for the revenue sharing (basic)
 *
 * @return
 *   HTML with the help text
 */
function revenue_sharing_basic_help_text() {
  global $user;
  $uid = $user->uid;

  $base = rtrim(base_path(), '/');

  $output = <<<EOF
<h2>Overview</h2>
<p>This module provides web site admins the factility to share revenue from
Google AdSense ads with those writing the content on the site, according to
certain percentages.</p>

<h2>Revenue sharing</h2>
<p>For revenue sharing, each author gets a predefined share of ad revenue from
clicks occuring on nodes they authored.</p>
<p>In order for the user to be credited they must have a Google AdSense
account.</p>
<p>Each user must enter their Google AdSense client ID in the profile field
you defined above.</p>

<h2>Configuration</h2>
<p>To use this module, you need to do the following first:</p>
<ul>
  <li>
    <p>Go to <a href="$base/admin/user/profile">Administer -&gt; User
    management -&gt; Profiles</a> and create a new profile field of type
    &quot;single-line textfield&quot;. Name this field something like
    &quot;Google AdSense client ID&quot;, and form name
    &quot;profile_google_adsense_client_id&quot;. This is a required
    configuration parameter.</p>
    <p>Note that the new profile field must be setup as: &quot;Private field,
    content only available to privileged users&quot;. All other values are
    either insecure (others can see the Google Adsense ID of the user), or
    will not work, so do not use any of them.</p>
    <p>If you want to force users to enter a value when they sign up, then use
    the following settings:</p>
    <ul>
      <li>The user must enter a value (checked).</li>
      <li>Visible in user registration form (checked).</li>
    </ul>
    <p>You should enter a descriptive explanation for the Google AdSense
    client ID, so users know what to enter in this field.</p></li>
  <li>Go to <a href="$base/user/$uid/edit">My account -&gt; Edit</a>, then
  click on the category that you defined for the Google AdSense client ID
  and enter your Google ID, which is something like
  &quot;pub-9999999999999&quot;, and click Submit.</li>
</ul>
EOF;

  return $output;
}
