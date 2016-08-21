'use strict';

(function ($, Drupal) {
  'use strict';

  Drupal.behaviors.plStarter = {
    attach: function attach(context, settings) {
      $('html', context).addClass('js');
      console.log('hello');
    }
  };
})(jQuery, Drupal);
//# sourceMappingURL=script.js.map
