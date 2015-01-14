<?php

/**
 * @file
 * Image assist administrative functionality.
 */

/**
 * Implementation of hook_settings().
 */
function img_assist_admin_settings() {
  require_once drupal_get_path('module', 'img_assist') .'/includes/img_assist.token.inc';

  // Access settings.
  $form['access'] = array(
    '#type' => 'fieldset',
    '#title' => t('Access settings'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  $form['access']['img_assist_paths_type'] = array(
    '#type' => 'radios',
    '#title' => t('Display Image assist on paths'),
    '#default_value' => variable_get('img_assist_paths_type', 2),
    '#options' => array(t('on specific paths'), t('not on specific paths'), t('all paths')),
  );
  $form['access']['img_assist_paths'] = array(
    '#type' => 'textarea',
    '#title' => t('Paths'),
    '#default_value' => variable_get('img_assist_paths', "node/*\ncomment/*"),
    '#cols' => 40,
    '#rows' => 5,
    '#description' => t("Enter one page per line as Drupal paths. The '*' character is a wildcard. Example paths are %blog for the blog page and %blog-wildcard for every personal blog. %front is the front page.", array('%blog' => 'blog', '%blog-wildcard' => 'blog/*', '%front' => '<front>')),
  );
  $form['access']['img_assist_textareas_type'] = array(
    '#type' => 'radios',
    '#title' => t('Display Image assist on text areas'),
    '#default_value' => variable_get('img_assist_textareas_type', 2),
    '#options' => array(t('Show on every textarea except the listed textareas.'), t('Show on only the listed textareas.'), t('Show on all textareas.')),
  );
  $form['access']['img_assist_textareas'] = array(
    '#type' => 'textarea',
    '#title' => t('Text areas'),
    '#default_value' => variable_get('img_assist_textareas', "edit-body\nedit-comment"),
    '#cols' => 40,
    '#rows' => 5,
    '#description' => t("Enter one text area form-id per line. Form-id's are used by Drupal to typify them, which allows themers and coders to modify certain form fields, but not all. Find form-id's using this method: view the source of the webpage, then search for the string that's just above the text area and you'll see the form-id nearby. The '*' character is a wildcard. For example, you can specify all CCK fields as %cck-example.", array('%cck-example' => 'edit-field-*')),
  );
  $form['access']['img_assist_link'] = array(
    '#type' => 'select',
    '#title' => t('Textarea image link'),
    '#default_value' => variable_get('img_assist_link', 'icon'),
    '#options' => array('icon' => t('Show icon'), 'text' => t('Show text link'), 'none' => t('Do not show a link')),
    '#description' => t('Choose what to show under the textareas for which Image assist is enabled.'),
  );

  // Prepare select options for image browser views.
  $options = array();
  views_include('admin');
  $views = views_get_all_views();
  $base_tables = views_fetch_base_tables();
  foreach ($views as $view) {
    // Exclude malformed views (@see views/admin.inc).
    if (!empty($view->disabled) || empty($view->display)) {
      continue;
    }
    // Exclude views considered unusable for IA.
    if (!($view->base_table == 'node' || $view->base_table == 'files')) {
      continue;
    }
    $options[$view->name] = ($view->get_title() == '') ? $view->name : $view->get_title();
  }
  $form['access']['img_assist_views'] = array(
    '#type' => 'select',
    '#multiple' => TRUE,
    '#title' => t('Image browser views'),
    '#default_value' => variable_get('img_assist_views', drupal_map_assoc(array('img_assist_browser'))),
    '#options' => $options,
    '#required' => TRUE,
    '#description' => t('Select the views to use for selecting images.'),
  );

  if (module_exists('taxonomy')) {
    $vocs = array(0 => '<'. t('none') .'>');
    foreach (taxonomy_get_vocabularies() as $vid => $voc) {
      $vocs[$vid] = $voc->name;
    }
    if (count($vocs) > 1) {
      $form['access']['img_assist_vocabs'] = array(
        '#type' => 'select',
        '#multiple' => TRUE,
        '#title' => t('Select the vocabularies to use for Image assist'),
        '#default_value' => variable_get('img_assist_vocabs', array()),
        '#options' => $vocs,
        '#description' => t('Select the vocabularies you want to be able to filter thumbnails by. This setting changes the behavior of Image assist at startup from loading all image thumbnails to displaying a list of image names until a filter is chosen.'),
      );
    }
  }
  
  // Image settings.
  $form['image'] = array(
    '#type' => 'fieldset',
    '#title' => t('Image generation settings'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  $form['image']['img_assist_max_size'] = array(
    '#type' => 'textfield',
    '#title' => t('Maximum inline image size allowed'),
    '#default_value' => variable_get('img_assist_max_size', '640x640'),
    '#size' => 9,
    '#maxlength' => 9,
    '#description' => t('Enter the number of maximum image dimensions to display with Image assist. This is a way to prevent users from breaking your layouts. This is applied when the filter tag is processed, so it will affect existing images. If an existing image exceeds these dimensions, a smaller derivative of the image will be substituted (or a smaller version will be created if you have allowed Image assist to create its own derivatives).'),
  );
  if (function_exists('image_get_sizes')) {
    $max_size = explode('x', variable_get('img_assist_max_size', '640x640'));
    $oversize_count = 0;
    foreach (image_get_sizes() as $key => $size) {
      $dimensions = $size['width'] .'x'. $size['height'];
      if ((!empty($size['width']) && $size['width'] <= $max_size[0]) || (!empty($size['height']) && $size['height'] <= $max_size[1])) {
        $derivatives[$dimensions] = $size['label'];
      }
      elseif ($key == IMAGE_THUMBNAIL) {
        // Thumbnail option is shown even if it is larger than maximum size.
        $derivatives[$dimensions] = $size['label'];
      }
      else {
        $oversize_count++;
      }
      $allsizes[$key] = $size['label'];
    }
    
    $form['image']['img_assist_popup_label'] = array(
      '#type' => 'select',
      '#title' => t('Popup size'),
      '#default_value' => variable_get('img_assist_popup_label', IMAGE_PREVIEW),
      '#options' => $allsizes,
      '#description' => t('Select the size of the image that is popped up.'),
    );
    
    $oversize_alert = ($oversize_count) ? '<br /><strong>'. format_plural($oversize_count, '1 image size is not being shown because it exceeds the the maximum inline image size setting (see above).', '@count image sizes are not being shown because they exceed the the maximum inline image size setting (see above).') .'</strong>' : '';
    $form['image']['img_assist_default_label'] = array(
      '#type' => 'select',
      '#title' => t('Default size for inline images'),
      '#default_value' => variable_get('img_assist_default_label', '100x100'),
      '#options' => $derivatives,
      '#description' => t('Select a derivative to be used by default for inline images.') . $oversize_alert,
    );
  }
  $form['image']['img_assist_create_derivatives'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Creation of image derivatives'),
    '#default_value' => variable_get('img_assist_create_derivatives', array()),
    '#options' => array(
      'properties' => t('Create 200x200 images for the image properties window (useful if the thumbnail size is small).'),
      'custom_advanced' => t('Allow users with %access permission to create custom size inline images.', array('%access' => 'access advanced options')),
      'custom_all' => t('Allow all users to create custom size inline images.'),
    ),
    '#description' => t('These options allow Image assist to generate its custom image sizes (in the same manner as image.module) when a user would prefer a different size from the default image sizes defined in the image.module settings.'),
  );
  
  // Other properties.
  $form['properties'] = array(
    '#type' => 'fieldset',
    '#title' => t('Image property dialog settings'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  $form['properties']['img_assist_default_link_behavior'] = array(
    '#type' => 'select',
    '#title' => t('Default link behavior'),
    '#default_value' => variable_get('img_assist_default_link_behavior', 'none'),
    '#options' => array('none' => t('Not a link'), 'node' => t('Link to image page'), 'popup' => t('Open in popup window'), 'url' => t('Go to URL')),
    '#description' => t('The link behavior can be overridden when inserting images by users with the proper permissions, but these defaults will still be used for everyone else.'),
  );
  $form['properties']['img_assist_default_link_url'] = array(
    '#type' => 'textfield',
    '#title' => t('Default URL'),
    '#default_value' => variable_get('img_assist_default_link_url', 'http://'),
    '#size' => 30,
    '#maxlength' => 255,
    '#description' => t('The default URL is used when Go to URL is choosen as the link behavior.'),
  );
  $form['properties']['img_assist_default_insert_mode'] = array(
    '#type' => 'select',
    '#title' => t('Default insert mode'),
    '#default_value' => variable_get('img_assist_default_insert_mode', 'none'),
    '#options' => array('filtertag' => t('Filter Tag'), 'html' => t('HTML Code')),
    '#description' => t('The insert behavior can be overridden by users with the %permission permission when inserting images.  <strong>Warning:</strong> If images are inserted as HTML, Image Assist is not able to correct a link or image URL afterwards.  Please also note that users will not be able to edit already inserted images when using HTML code and the TinyMCE plugin.', array('%permission' => t('access advanced options'))),
  );
  $form['properties']['img_assist_load_title'] = array(
    '#type' => 'radios',
    '#title' => t('Preset caption title'),
    '#default_value' => variable_get('img_assist_load_title', 1),
    '#options' => array(t('Disabled'), t('Enabled')),
    '#description' => t('If enabled, the title from the image will be loaded as the bolded caption by default.'),
  );
  $token_installed = module_exists('token');
  $token_instructions = (!$token_installed ? t('Requires the !token module.', array('!token' => l('Token', 'http://drupal.org/project/token'))) : t('See below for a list of available replacement patterns.'));
  $form['properties']['img_assist_title_pattern'] = array(
    '#type' => 'textfield',
    '#title' => t('Caption title pattern'),
    '#default_value' => variable_get('img_assist_title_pattern', '[title]'),
    '#size' => 60,
    '#maxlength' => 255,
    '#description' => t('The pattern to generate the bolded caption title from.') .' '. $token_instructions,
    '#disabled' => !$token_installed,
  );
  $form['properties']['img_assist_load_description'] = array(
    '#type' => 'radios',
    '#title' => t('Preset caption text'),
    '#default_value' => variable_get('img_assist_load_description', 1),
    '#options' => array(t('Disabled'), t('Enabled')),
    '#description' => t('If enabled, the body text from the image will be loaded as the caption by default.'),
  );
  $form['properties']['img_assist_description_pattern'] = array(
    '#type' => 'textfield',
    '#title' => t('Caption text pattern'),
    '#default_value' => variable_get('img_assist_description_pattern', '[body]'),
    '#size' => 60,
    '#maxlength' => 255,
    '#description' => t('The pattern to generate the caption text from.') .' '. $token_instructions,
    '#disabled' => !$token_installed,
  );
  if ($token_installed) {
    $form['properties']['token_help'] = array(
      '#title' => t('Replacement patterns'),
      '#type' => 'fieldset',
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
    );
    $form['properties']['token_help'][] = array(
      '#value' => theme('token_help', 'node'),
    );
  }
  if (module_exists('content')) {
    $options = array();
    $info = _content_type_info();
    foreach ($info['content types']['image']['fields'] as $field) {
      $options[$field['field_name']] = t($field['widget']['label']) .' ('. $field['field_name'] .')';
    }
    $form['properties']['img_assist_display_properties'] = array(
      '#type' => 'checkboxes',
      '#title' => t('Image properties shown'),
      '#default_value' => variable_get('img_assist_display_properties', array()),
      '#options' => $options,
      '#description' => t('All selected CCK fields from the Image node will be displayed in the Image Assist pop-up window.'),
    );
    if (empty($options)) {
      $form['properties']['img_assist_display_properties']['#description'] .= '<br />'. t('<strong>Note:</strong> The <a href="!content-type">Image content-type</a> does not contain any CCK fields currently.', array('!content-type' => url('admin/content/node-type/image/fields')));
    }
  }
  
  // Image display settings.
  $form['display'] = array(
    '#type' => 'fieldset',
    '#title' => t('Image display settings'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  $form['display']['img_assist_page_styling'] = array(
    '#type' => 'select',
    '#title' => t('Include img_assist.css on all pages for styling inline images?'),
    '#default_value' => variable_get('img_assist_page_styling', 'yes'),
    '#options' => array('yes' => t('yes'), 'no' => t('no')),
    '#description' => t('Advanced users can customize their theme\'s CSS file so that inclusion of the img_assist.css file will not be necessary. See notes at the bottom of img_assist.css for details.'),
  );
  
  return system_settings_form($form);
}

/**
 * Validate Image Assist settings.
 */
function img_assist_admin_settings_validate($form, &$form_state) {
  // img_assist_max_size must contain a value for width and height.
  if (!preg_match('/\d+x\d+/', $form_state['values']['img_assist_max_size'])) {
    form_set_error('img_assist_max_size', t('Allowed maximum inline image size has to indicate width and height, for example %example.', array('%example' => '200x300')));
  }
}

/**
 * Menu callback; clears relevant caches, then redirects to the previous page.
 *
 * @see devel_cache_clear()
 */
function img_assist_cache_clear() {
  // clear core tables
  $core = array('cache_filter', 'cache_page');
  foreach ($core as $table) {
    cache_clear_all('*', $table, TRUE);
  }
  drupal_set_message('Cache cleared.');
  drupal_goto('admin/settings/img_assist');
}

