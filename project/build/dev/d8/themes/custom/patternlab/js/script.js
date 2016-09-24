(function($, Drupal) {
  'use strict';

  Drupal.behaviors.plStarter = {
    attach: function(context, settings) {
      $('html', context).addClass('js');
      console.log('hello');
    }
  };

  Drupal.behaviors.mediaModal = {
    attach: function(context, settings) {
      $('#media-modal', context).on('show.bs.modal', function(event) {
        var $trigger = $(event.relatedTarget);
        $(this)
          .find('#modal-media').attr('src', $trigger.data('modal-media')).end()
          .find('#modal-title').html($trigger.data('modal-title'));
      });
    }
  };

})(jQuery, Drupal);
