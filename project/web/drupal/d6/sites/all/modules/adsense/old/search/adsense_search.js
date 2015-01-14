
if (Drupal.jsEnabled) {
  $(document).ready(function () {
    // initiate farbtastic colorpicker
    var farb = $.farbtastic("#colorpicker");
    var firstField = "";

    $("input.form-text").each( function() {
      if (this.name.substring(0, 20) == "adsense_search_color") {
        if (firstField == "") {
          firstField = this;
        };

        farb.linkTo(this);
        $(this).click(function () {
          farb.linkTo(this);
        });
      };
    });

    farb.linkTo(firstField);
  });
}
