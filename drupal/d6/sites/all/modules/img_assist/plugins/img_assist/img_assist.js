
Drupal.wysiwyg.plugins.img_assist = {

  /**
   * Return whether the passed node belongs to this plugin.
   */
  isNode: function (node) {
    return $(node).is('img.img-assist');
  },

  /**
   * Execute the button.
   */
  invoke: function (data, settings, instanceId) {
    if (data.format == 'html') {
      // captionTitle and captionDesc for backwards compatibility.
      var options = {nid: '', title: '', captionTitle: '', desc: '', captionDesc: '', link: '', url: '', align: '', width: '', height: '', id: instanceId, action: 'insert'};
      if ($(data.node).is('img.img-assist')) {
        options.width = data.node.width;
        options.height = data.node.height;
        options.align = data.node.align;
        // Expand inline tag in alt attribute
        data.node.alt = decodeURIComponent(data.node.alt);
        var chunks = data.node.alt.split('|');
        for (var i in chunks) {
          chunks[i].replace(/([^=]+)=(.*)/g, function(o, property, value) {
            options[property] = value;
          });
        }
        options.captionTitle = options.title;
        options.captionDesc = options.desc;
        options.action = 'update';
      }
    }
    else {
      // @todo Plain text support.
    }
    if (typeof options != 'undefined') {
      Drupal.wysiwyg.instances[instanceId].openDialog(settings.dialog, options);
    }
  },

  /**
   * Replace inline tags in content with images.
   */
  attach: function (content, settings, instanceId) {
    content = content.replace(/\[img_assist\|([^\[\]]+)\]/g, function(orig, match) {
      var node = {}, chunks = match.split('|');
      for (var i in chunks) {
        chunks[i].replace(/([^=]+)=(.*)/g, function(o, property, value) {
          node[property] = value;
        });
      }
      // 'class' is a predefined token in JavaScript.
      node['class'] = 'img-assist drupal-content';
      node.src = Drupal.settings.basePath + 'index.php?q=image/view/' + node.nid;
      node.alt = 'nid=' + node.nid + '|title=' + node.title + '|desc=' + node.desc;
      if (node.link.indexOf(',') != -1) {
        var link = node.link.split(',', 2);
        node.alt += '|link=' + link[0] + '|url=' + link[1];
      }
      else {
        node.alt += '|link=' + node.link;
      }
      if (typeof node.url != 'undefined') {
        node.alt += '|url=' + node.url;
      }
      node.alt = encodeURIComponent(node.alt);
      var element = '<img ';
      for (var property in node) {
        element += property + '="' + node[property] + '" ';
      }
      element += '/>';
      return element;
    });
    return content;
  },

  /**
   * Replace images with inline tags in content upon detaching editor.
   */
  detach: function (content, settings, instanceId) {
    var $content = $('<div>' + content + '</div>'); // No .outerHTML() in jQuery :(
    $('img.img-assist', $content).each(function(node) {
      var inlineTag = '[img_assist|' + decodeURIComponent(this.alt) + '|align=' + this.align + '|width=' + this.width + '|height=' + this.height + ']';
      $(this).replaceWith(inlineTag);
    });
    return $content.html();
  }
};
