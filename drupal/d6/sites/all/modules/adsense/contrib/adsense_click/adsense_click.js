/* $Id */

/**
 * adsense_click.js - fires counter to log adsense clicks
 */
var lastStatus = '';

function adsense_click(e) {
  window.focus();
  if (window.status && (window.status != lastStatus)) {
    lastStatus = window.status;
    var img = new Image();
    img.src = window.location.protocol + '//' + window.location.host + '/adsense_click' +
      '?u=' + escape(document.location) +
      '&t=' + escape(document.title) +
      '&r=' + escape(document.referrer);
  }
}

var iframeObj;
var elements;
elements = document.getElementsByTagName("iframe");
for (var i = 0; i < elements.length; i++) {
  if(elements[i].src.indexOf('googlesyndication.com') > -1) {
    if (document.layers) {
      elements[i].captureEvents(Events.ONFOCUS);
    }
    elements[i].onfocus = adsense_click;
    iframeObj = elements[i];
  }
}

