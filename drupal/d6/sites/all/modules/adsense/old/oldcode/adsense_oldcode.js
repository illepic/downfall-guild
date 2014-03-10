
if (Drupal.jsEnabled) {
  $(document).ready(function () {
    var i = 0;

    for (i = 1; i <= 5; i++) {
      // initiate farbtastic colorpicker
      var farb = $.farbtastic("#colorpicker-" + i);
      var firstField = "";

      $("input.form-text").each( function() {
        if (this.name.substring(0, 13) == "adsense_color") {
          if (this.name.substring(this.name.lastIndexOf("_") + 1) == i) {
            if (firstField == "") {
              firstField = this;
            };

            farb.linkTo(this);
            $(this).click(function () {
              var clickGroup = this.name.substring(this.name.lastIndexOf("_") + 1);
              $.farbtastic("#colorpicker-" + clickGroup).linkTo(this);
            });
          };
        };
      });

      farb.linkTo(firstField);
    };
  });
}
