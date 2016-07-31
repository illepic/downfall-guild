(function($, Drupal) {
  'use strict';

  Drupal.behaviors.plStarter = {
    attach: function(context, settings) {
      $('html', context).addClass('js');
      console.log('hello');
    }
  };

})(jQuery, Drupal);
