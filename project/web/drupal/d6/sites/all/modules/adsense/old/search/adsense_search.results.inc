<?php

/**
 * @file
 * Displays the page containing the results of the Adsense for Search box
 */

/**
 * Creates the Adsense for Search search results page for site-embedded search results
 *
 * @return
 *   JavaScript that embeds the Google results
 */
function _adsense_search_results() {
  // Log the search keys:
  watchdog('AdSense', 'Search keywords: %keyword', array('%keyword' => urldecode($_GET['as_q'])), WATCHDOG_NOTICE);

  // Output search results
  $width   = variable_get('adsense_search_frame_width', ADSENSE_SEARCH_FRAME_WIDTH_DEFAULT);
  $country = variable_get('adsense_search_country', ADSENSE_SEARCH_COUNTRY_DEFAULT);

  if (variable_get('adsense_test_mode', ADSENSE_TEST_MODE_DEFAULT)) {
    $output = theme('adsense_placeholder', "Results<br />width = ${width}<br />country = ${country}", $width, 100);
  }
  else {
    if (variable_get('adsense_secret_adtest', ADSENSE_SECRET_ADTEST_DEFAULT)) {
      $secret = '  var googleAdtest = "on";';
    }

    $output = <<<SEARCH_RESULTS_TXT
<!-- Google Search Result Snippet Begins -->
<div id="googleSearchUnitIframe"></div>
<script type="text/javascript">
  var googleSearchIframeName = 'googleSearchUnitIframe';
  var googleSearchFrameWidth = $width;
  var googleSearchFrameborder = 0 ;
  var googleSearchDomain = '$country';
$secret
</script>
<script type="text/javascript"
  src="http://www.google.com/afsonline/show_afs_search.js">
</script>
<!-- Google Search Result Snippet Ends -->
SEARCH_RESULTS_TXT;

    // Remove empty lines
    $output = str_replace("\n\n", "\n", $output);
  }

  return $output;
}

