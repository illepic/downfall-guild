(function secondaryThemeScript($, Drupal) {
  Drupal.behaviors.demo2 = {
    attach: function demo2Test(context) {
      $('html', context).addClass('js2');
    },
  };
}(jQuery, Drupal));
