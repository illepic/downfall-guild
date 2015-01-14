<?php
class views_tabs_plugin_style extends views_plugin_style {
  function options(&$options) {
    parent::options($options);
    if ($this->row_plugin->definition['uses fields']) {
      $options['tab_field'] = 'title';
    }
  }
  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);
    if ($this->uses_fields() && $this->definition['uses grouping']) {
      $options = $this->options;
      $opt = array('' => t('<None>'));
      foreach ($this->display->handler->get_handlers('field') as $field => $handler) {
        if ($label = $handler->label()) {
          $opt[$field] = $label;
        }
        else {
          $opt[$field] = $handler->ui_name();
        }
      }
      $form['tab_field'] = array(
        '#title' => t('Tab field'),
        '#type'  => 'select',
        '#options' => $opt,
        '#default_value' => $options['tab_field'],
      );
    }
  }
  function render() {
    $this->definition['theme'] = $this->row_plugin->definition['theme'];
    if ($this->uses_row_plugin() && empty($this->row_plugin)) {
      vpr('views_plugin_style_default: Missing row plugin');
      return;
    }
    $tabset = array(
      '#type' => 'tabset',
    );
    // Group the rows according to the grouping field, if specified.
    $sets = $this->render_grouping($this->view->result, $this->options['grouping']);
    // Render each group separately and concatenate.  Plugins may override this
    // method if they wish some other way of handling grouping.
    $output = '';
    $this->view->row_index = 0;
    foreach ($sets as $title => $records) {
      $content = '';
      if ($this->uses_row_plugin()) {
        $rows = array();
        foreach ($records as $label => $row) {
          if ($this->uses_fields()) {
            $content .= theme($this->theme_functions(), $this->view, $this->options, $this->row_plugin->render($row));
          } else {
            $node = node_load($row->nid);
            $node->view = $this->view;
            $options = $this->row_plugin->options;
            $node->build_mode = ($options['build_mode'] == 'teaser' || $options['build_mode'] == 'full') ? NODE_BUILD_NORMAL : $options['build_mode'];
            $content = node_view($node, $options['build_mode'] == 'teaser', FALSE, $options['links']);
            $title = $node->title;
            if (!$tabset[$title]) {
              $tabset[$title] = array(
                '#type' => 'tabpage',
                '#content' => $content,
                '#title' => $title,
                '#attributes' => array('class' => 'tab-title'),
              );
            }
          }
          $this->view->row_index++;
        }
      } else {
        $rows = $records;
      }
      if (!$tabset[$title] && $this->uses_fields()) {
        $tabset[$title] = array(
          '#type' => 'tabpage',
          '#content' => $content,
          '#title' => $title,
          '#attributes' => array('class' => 'tab-title'),
        );
      } else {
        $tabset[$title]['#content'] .= $content;
      }
    }
    unset($this->view->row_index);
    return drupal_render($tabset);
  }
}
