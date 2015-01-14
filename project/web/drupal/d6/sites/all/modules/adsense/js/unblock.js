if (Drupal.jsEnabled) {
  function detectAdBlock() {
    if ($('.adsense ins').contents().length == 0) {
      $('.adsense').html(Drupal.t("Please, enable ads on this site. By using ad-blocking software, you're depriving this site of revenue that is needed to keep it free and current. Thank you."));
      $('.adsense').css({'overflow': 'hidden', 'font-size': 'smaller'});
    }
  }

  $(document).ready(function () {
    detectAdBlock();
  });
}
