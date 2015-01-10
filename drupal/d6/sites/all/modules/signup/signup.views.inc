<?php
// $Id$

/**
 * @file
 * Provides support for Views integration.
 *
 * This exposes signup-related data and provides fields, filters,
 * sorts, and arguments.
 *
 * Additionally, default views for standard parts of the signup UI are
 * defined here.  If views is not enabled, these UI elements are
 * implemented in signup_no_views.inc.
 */

/**
 * Implementation of hook_views_data
 */
function signup_views_data() {
  // Define the base group of the signup table.  Fields that don't
  // have a group defined will go into this field by default.
  $data['signup']['table']['group'] = t('Signup');

  $data['signup']['table']['join'] = array(
    'node' => array(
      'left_field' => 'nid',
      'field' => 'nid',
    ),
  );

  $data['signup']['status'] = array(
    'title' => t('Status: Open/Closed'),
    'help' => t('Are signups open or closed for this node?'),
    // Information for displaying the field
    'field' => array(
      'handler' => 'views_handler_field_signup_status',
      'click sortable' => TRUE,
    ),
    // Information for accepting status as a filter
    'filter' => array(
      'handler' => 'views_handler_filter_signup_status',
      'help' => t('Filter on if signups are open or closed for each node.'),
      'label' => 'Open',
    ),
    // Information for sorting on status
    'sort' => array(
      'handler' => 'views_handler_sort',
      'help' => t('Sort by if signups are closed or open.'),
    ),
  );

  $data['signup']['close_signup_limit'] = array(
    'title' => t('Signup Limit'),
    'help' => t('Maximum number of users who can sign up before signups are automatically closed (set to 0 for no limit).'),
    // Information for displaying the field
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    // Information for accepting close_signup_limit as a filter
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
      'help' => t('Filter by the maximum number of users who can sign up before signups are automatically closed (set to 0 for no limit).'),
    ),
  );

  $data['signup']['forwarding_email'] = array(
    'title' => t('Notification: Email Address'),
    'help' => t('Address where notification emails are sent wenever a user signs up.'),
    // Information for displaying the field
    'field' => array(
      'handler' => 'views_handler_field',
    ),
  );

  $data['signup']['send_confirmation'] = array(
    'title' => t('Confirmation: Enabled/Disabled'),
    'help' => t('Should confirmation email be sent to each user who signs up.'),
    // Information for displaying the field
    'field' => array(
      'handler' => 'views_handler_field_signup_send_confirmation',
      'click sortable' => TRUE,
    ),
    // Information for accepting send_confirmation as a filter
    'filter' => array(
      'handler' => 'views_handler_filter_signup_send_confirmation',
      'help' => t('Filter on if signup confirmation is enabled or disabled.'),
    ),
  );

  $data['signup']['confirmation_email'] = array(
    'title' => t('Confirmation: Message'),
    'help' => t('The body of the optional confirmation email that can be sent whenever a user signs up.'),
    // Information for displaying the field
    'field' => array(
      'handler' => 'views_handler_field',
    ),
  );

  $data['signup']['send_reminder'] = array(
    'title' => t('Reminder: Enabled/Disabled'),
    'help' => t('Should a reminder email be automatically sent to all users who signed up. This will be false if either an administrator disabled the feature for a given event, or if the reminder was already sent.'),
    // Information for displaying the field
    'field' => array(
      'handler' => 'views_handler_field_boolean',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_field_boolean_operator',
      'help' => t('Filter on signup reminder'),
    ),
  );

  $data['signup']['reminder_days_before'] = array(
    'title' => t('Reminder: Days Before Event for Email'),
    'help' => t('How many days before an event will the reminder email be sent.'),
    // Information for displaying the field
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
  );
      
  $data['signup']['reminder_email'] = array(
    'title' => t('Reminder: Message'),
    'help' => t('The body of the optional reminder email that can be sent a configurable time before an event begins.'),
    // Information for displaying the field
    'field' => array(
      'handler' => 'views_handler_field',
    ),
  );

  $data['signup']['signup_disabled'] = array(
    'title' => t('Enabled/Disabled'),
    'filter' => array(
      'handler' => 'views_handler_filter_signup_disabled',
      'help' => t('Filter on if signups are enabled or disabled'),
      'label' => 'Enabled',
      ),
  );

  // Define base group for signup_log table.
  $data['signup_log']['table']['group'] = t('Signup');

  $data['signup_log']['table']['join'] = array(
    'node' => array(
      'left_field' => 'nid',
      'field' => 'nid',
    ),
  );

  $data['signup_log']['uid'] = array(
    'title' => t('User: Name'),
    'help' => t('Username of an authenticated user who signed up, or %anonymous for anonymous signups.', array('%anonymous' => variable_get('anonymous', t('Anonymous')))),
    // Information for displaying the field
    'field' => array(
      'handler' => 'views_handler_field_signup_username',
      'click sortable' => true,
    ),
  );

  $data['signup_log']['email'] = array(
    'title' => t('User: Email Address'),
    'handler' => 'views_handler_field_signup_email',
    'click sortable' => true,
    'field' => 'uid',
    'addlfields' => array('anon_mail'),
    'help' => t('Email address of a user (authenticated or anonymous) who signed up.') .' <strong>'. t('WARNING: only expose this data in a view that is restricted to users whom you can trust with such sensitive information.') .'</strong>',
  );

  $data['signup_log']['signup_time'] = array(
    'title' => t('User: Signup Time'),
    'help' => t('Time when user signed up.'),
    'field' => array(
      'handler' => 'views_handler_field_date',
      'click sortable' => true,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_date',
      'help' => t('Time when user signed up.'),
    ),
    'sort' => array(
      'handler' => 'views_handler_sort_date',
      'help' => t('Sort by time of sign up.'),
    ),
  );

  $data['signup_log']['form_data'] = array(
    'title' => t('User: Additional Signup Info'),
    'help' => t('Enter the additional field name (from signup.theme) in the Option column.'),
    'field' => array(
      'handler' => 'views_handler_field_signup_form_data',
      'option' => 'string',
    ),
  );

  $data['signup_log']['signup_user_auth'] = array(
    'title' => t('User: Anonymous/Authenticated'),
    'real field' => 'uid',
    'filter' => array(
      'handler' => 'views_handler_filter_signup_user_auth',
      'help' => t('Filter on if a user who signed up is anonymous, or an authenticated user on the site.'),
      'label' => t('Authenticated'),
    ),
  );

  $data['signup_log']['signup_user_current'] = array(
    'title' => t('User: Current User'),
    'real field' => 'uid',
    'filter' => array(
      'handler' => 'views_handler_filter_user_current',
      'help' => t('This allows you to filter by whether or not the node was signed up by the logged in user of the view.'),
    ),
  );

  /**
   * TODO: add argument field
   */
  $data['signup_log']['signup_uid'] = array(
    'title' => t('User: UID Signup for Node'),
    'help' => t('Filter signups by signed up user.'),
    'real field' => 'uid',
    'argument' => array(
      'handler' => 'views_handler_argument_signup_uid',
     ),
  );

  return $data;
}

class views_handler_field_signup_status extends views_handler_field {
  function render($values) {
    return ($values->{$this->field_alias} == 0) ? t('Closed') : t('Open');
  }
}

class views_handler_filter_signup_status extends views_handler_filter_boolean_operator {
  function admin_summary() {
    if (!empty($this->options['exposed'])) {
      return t('exposed');
    }

    return (empty($this->value) ? t("Closed") : t('Open'));
  }
}

class views_handler_field_signup_send_confirmation extends views_handler_field {
  function render($values) {
    return ($values->{$this->field_alias} == 0) ? t('Disabled') : t('Enabled');
  }
}

class views_handler_filter_signup_send_confirmation extends views_handler_filter_boolean_operator {
  function admin_summary() {
    if (!empty($this->options['exposed'])) {
      return t('exposed');
    }

    return (empty($this->value) ? t("Disabled") : t('Enabled'));
  }
}

class views_handler_filter_signup_disabled extends views_handler_filter_boolean_operator {
  function admin_summary() {
    if (!empty($this->options['exposed'])) {
      return t('exposed');
    }

    return (empty($this->value) ? t("Disabled") : t('Enabled'));
  }

  function query() {
    $this->ensure_my_table();
    $this->query->add_where($this->options['group'], "$this->table_alias.nid " . (empty($this->value) ? 'IS ' : 'IS NOT ') . "NULL");
  }
}

class views_handler_field_signup_username extends views_handler_field {
  function render($values) {
    $account = user_load(array('uid' => $values->{$this->field_alias}));
    return theme('username', $account);
  }
}

class views_handler_field_signup_form_data extends views_handler_field_prerender_list {
  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);
    $form['form_data_fieldname'] = array(
      '#type' => 'textfield',
      '#title' => t(' Field Name'),
      '#description' => t('If you want to display a single field from signup.theme, enter its name here, otherwise, all fields will be displayed.'),
      '#default_value' => isset($this->options['form_data_fieldname']) ? $this->options['form_data_fieldname'] : '',
    );
  }

  function pre_render($values) {
    if (!$this->options['form_data_fieldname']) {
      foreach ($values as $key => $result) {
        $form_data = unserialize($result->{$this->field_alias});
        if ($form_data) {
          foreach ($form_data as $key => $value) {
            $this->items[$result->{$this->field_alias}][$key] = check_plain($key .': '. $value);
          }
        }
      }
    }
  }

  function render($values) {
    if ($this->options['form_data_fieldname']) {
      $form_data = unserialize($values->{$this->field_alias});
      return check_plain($form_data[$this->options['form_data_fieldname']]);
    } else {
      return parent::render($values);
    }
  }
}

class views_handler_filter_signup_user_auth extends views_handler_filter_boolean_operator {
  function admin_summary() {
    if (!empty($this->options['exposed'])) {
      return t('exposed');
    }

    return (empty($this->value) ? t("Anonymous") : t('Authenticated'));
  }

  function query() {
    $this->ensure_my_table();
    $this->query->add_where($this->options['group'], "$this->table_alias.$this->real_field " . ($this->value ? '!= ' : '= ') . "0");
  }
}

class views_handler_argument_signup_uid extends views_handler_argument_numeric {
  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);

    // remove 'not' form element, as it doesn't make sense for this argument
    // instead, we need to add a custom form element to show nodes the user
    // hasn't signed up for
    unset($form['not']);
    $form['not_signed_up'] = array(
      '#type' => 'checkbox',
      '#title' => t('Exclude signed up nodes.'),
      '#description' => t('If selected, the view will display nodes the user hasn\'t signed up for, rather than nodes the user has signed up for.'),
      '#default_value' => !empty($this->options['not_signed_up']),
    );
  }
  function query() {
    if (!empty($this->options['not_signed_up'])) {
      $join = $this->get_join();
      $join->extra = "$this->table.$this->real_field = $this->argument";
      $this->query->ensure_table($this->table, NULL, $join);
      $this->query->add_where(0, "$this->table.$this->real_field IS NULL");
    } else {
      parent::query();
    }
  }
}
