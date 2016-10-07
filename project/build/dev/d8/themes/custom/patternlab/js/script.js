(function dfMain($, Drupal) {
  // Shared, reusable data and helpers
  const df = {
    breakpoints: {
      sm: 768,
      md: 992,
      lg: 1200,
    },
    parallax: ($element) => {
      const offset = ($(window).scrollTop() / 3).toFixed();
      $element.css({ transform: `translate3d(0, ${offset}px, 0` });
    },
  };

  /**
   * Generic media modal with dynamic title and img src
   *
   */
  Drupal.behaviors.mediaModal = {
    attach: (context) => {
      $('#media-modal', context).on('show.bs.modal', (event) => {
        const $trigger = $(event.relatedTarget);
        $(this)
          .find('#modal-media').attr('src', $trigger.data('modal-media')).end()
          .find('#modal-title')
            .html($trigger.data('modal-title'));
      });
    },
  };

  /**
   * page-header parallax
   */
  Drupal.behaviors.pageHeaderParallax = {
    attach: (context) => {
      const $parallaxElement = $('[data-parallax="active"]', context);

      // Only do this for tablet+ or no header
      if ($(window).width() < df.breakpoints.sm || $parallaxElement.length === 0) { return; }

      function lax() {
        if (!$parallaxElement.is(':in-viewport')) { return; }
        // console.info('Running lax');

        window.requestAnimationFrame(() => {
          df.parallax($parallaxElement);
        });
      }

      // Consider this if current 'lax is to resource intense
      // $(window).on('scroll', _.throttle(lax, 100));
      $(window).on('scroll', lax);
    },
  };
}(jQuery, Drupal));
