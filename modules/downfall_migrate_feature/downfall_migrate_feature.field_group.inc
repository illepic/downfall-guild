<?php
/**
 * @file
 * downfall_migrate_feature.field_group.inc
 */

/**
 * Implements hook_field_group_info().
 */
function downfall_migrate_feature_field_group_info() {
  $export = array();

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_app_char_info|node|guild_app|form';
  $field_group->group_name = 'group_app_char_info';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'guild_app';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Character Info',
    'weight' => '1',
    'children' => array(
      0 => 'field_app_char_name',
      1 => 'field_app_race',
      2 => 'field_app_class',
      3 => 'field_app_level',
      4 => 'field_app_max_time',
      5 => 'field_app_current_server',
      6 => 'field_app_current_server_time',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'label' => 'Character Info',
      'instance_settings' => array(
        'required_fields' => 1,
        'classes' => '',
        'description' => 'Please fill out the information about your character.',
      ),
      'formatter' => 'collapsible',
    ),
  );
  $export['group_app_char_info|node|guild_app|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_app_general|node|guild_app|form';
  $field_group->group_name = 'group_app_general';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'guild_app';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'General Questions',
    'weight' => '3',
    'children' => array(
      0 => 'field_app_why_recruit',
      1 => 'field_app_why_apply',
      2 => 'field_app_get_out_of_membership',
      3 => 'field_app_contribute_community',
      4 => 'field_app_references',
      5 => 'field_app_duration_of_stay',
      6 => 'field_app_cause_leave',
      7 => 'field_app_timezone',
      8 => 'field_app_anything_else',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'label' => 'General Questions',
      'instance_settings' => array(
        'required_fields' => 1,
        'classes' => '',
        'description' => 'These are just all the other questions we\'d no doubt ask you in person ;)',
      ),
      'formatter' => 'collapsible',
    ),
  );
  $export['group_app_general|node|guild_app|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_app_personal|node|guild_app|form';
  $field_group->group_name = 'group_app_personal';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'guild_app';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Personal',
    'weight' => '5',
    'children' => array(
      0 => 'field_app_how_long_wow',
      1 => 'field_app_how_old',
      2 => 'field_app_yourself',
      3 => 'field_app_school_or_work',
      4 => 'field_app_hobbies',
      5 => 'field_app_country_state',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'label' => 'Personal',
      'instance_settings' => array(
        'required_fields' => 1,
        'classes' => '',
        'description' => 'Tell us about you the person.',
      ),
      'formatter' => 'collapsible',
    ),
  );
  $export['group_app_personal|node|guild_app|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_app_raiding|node|guild_app|form';
  $field_group->group_name = 'group_app_raiding';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'guild_app';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Raiding',
    'weight' => '2',
    'children' => array(
      0 => 'field_app_talents',
      1 => 'field_app_role_comfortable',
      2 => 'field_app_class_contributes',
      3 => 'field_app_instances_experience',
      4 => 'field_app_boss_favorite',
      5 => 'field_app_boss_least_favorite',
      6 => 'field_app_raid_nights',
      7 => 'field_app_pvp_interest',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'label' => 'Raiding',
      'instance_settings' => array(
        'required_fields' => 1,
        'classes' => '',
        'description' => 'Downfall likes to raid. Though we like fun, smart people, we generally invite based on what you can bring to the table regarding 5-mans as well as 10- and 25-man raids. Please answer the following questions in regards to your raiding capacity.',
      ),
      'formatter' => 'collapsible',
    ),
  );
  $export['group_app_raiding|node|guild_app|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_app_ui|node|guild_app|form';
  $field_group->group_name = 'group_app_ui';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'guild_app';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'UI',
    'weight' => '4',
    'children' => array(
      0 => 'field_app_ui',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'label' => 'UI',
      'instance_settings' => array(
        'required_fields' => 1,
        'classes' => '',
        'description' => 'We like addons, they make our jobs easier. Talk to us about them.',
      ),
      'formatter' => 'collapsible',
    ),
  );
  $export['group_app_ui|node|guild_app|form'] = $field_group;

  return $export;
}
