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
  $field_group->identifier = 'group_char_info_edit|node|guild_app|form';
  $field_group->group_name = 'group_char_info_edit';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'guild_app';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Character Information',
    'weight' => '1',
    'children' => array(
      0 => 'field_app_char_name',
      1 => 'field_app_class',
      2 => 'field_app_current_server',
      3 => 'field_app_current_server_time',
      4 => 'field_app_level',
      5 => 'field_app_max_time',
      6 => 'field_app_race',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-char-info-edit field-group-fieldset',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_char_info_edit|node|guild_app|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_char_info|node|guild_app|default';
  $field_group->group_name = 'group_char_info';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'guild_app';
  $field_group->mode = 'default';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Character Info',
    'weight' => '0',
    'children' => array(
      0 => 'field_app_char_name',
      1 => 'field_app_class',
      2 => 'field_app_current_server',
      3 => 'field_app_current_server_time',
      4 => 'field_app_level',
      5 => 'field_app_max_time',
      6 => 'field_app_race',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-char-info field-group-fieldset',
      ),
    ),
  );
  $export['group_char_info|node|guild_app|default'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_guild_info_edit|node|guild_app|form';
  $field_group->group_name = 'group_guild_info_edit';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'guild_app';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Guild Information',
    'weight' => '3',
    'children' => array(
      0 => 'field_app_cause_leave',
      1 => 'field_app_contribute_community',
      2 => 'field_app_duration_of_stay',
      3 => 'field_app_get_out_of_membership',
      4 => 'field_app_pvp_interest',
      5 => 'field_app_references',
      6 => 'field_app_why_apply',
      7 => 'field_app_why_recruit',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-guild-info-edit field-group-fieldset',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_guild_info_edit|node|guild_app|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_guild_info|node|guild_app|default';
  $field_group->group_name = 'group_guild_info';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'guild_app';
  $field_group->mode = 'default';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Guild Information',
    'weight' => '2',
    'children' => array(
      0 => 'field_app_cause_leave',
      1 => 'field_app_contribute_community',
      2 => 'field_app_duration_of_stay',
      3 => 'field_app_get_out_of_membership',
      4 => 'field_app_pvp_interest',
      5 => 'field_app_references',
      6 => 'field_app_why_apply',
      7 => 'field_app_why_recruit',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-guild-info field-group-fieldset',
      ),
    ),
  );
  $export['group_guild_info|node|guild_app|default'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_person_info_edit|node|guild_app|form';
  $field_group->group_name = 'group_person_info_edit';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'guild_app';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Person Information',
    'weight' => '4',
    'children' => array(
      0 => 'field_app_anything_else',
      1 => 'field_app_country_state',
      2 => 'field_app_hobbies',
      3 => 'field_app_how_long_wow',
      4 => 'field_app_how_old',
      5 => 'field_app_school_or_work',
      6 => 'field_app_timezone',
      7 => 'field_app_yourself',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-person-info-edit field-group-fieldset',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_person_info_edit|node|guild_app|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_person_info|node|guild_app|default';
  $field_group->group_name = 'group_person_info';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'guild_app';
  $field_group->mode = 'default';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Person Information',
    'weight' => '3',
    'children' => array(
      0 => 'field_app_anything_else',
      1 => 'field_app_country_state',
      2 => 'field_app_hobbies',
      3 => 'field_app_how_long_wow',
      4 => 'field_app_how_old',
      5 => 'field_app_school_or_work',
      6 => 'field_app_timezone',
      7 => 'field_app_yourself',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-person-info field-group-fieldset',
      ),
    ),
  );
  $export['group_person_info|node|guild_app|default'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_raid_info_edit|node|guild_app|form';
  $field_group->group_name = 'group_raid_info_edit';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'guild_app';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Raid Information',
    'weight' => '2',
    'children' => array(
      0 => 'field_app_boss_favorite',
      1 => 'field_app_boss_least_favorite',
      2 => 'field_app_class_contributes',
      3 => 'field_app_instances_experience',
      4 => 'field_app_raid_nights',
      5 => 'field_app_role_comfortable',
      6 => 'field_app_talents',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-raid-info-edit field-group-fieldset',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_raid_info_edit|node|guild_app|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_raid_info|node|guild_app|default';
  $field_group->group_name = 'group_raid_info';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'guild_app';
  $field_group->mode = 'default';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Raid Information',
    'weight' => '1',
    'children' => array(
      0 => 'field_app_boss_favorite',
      1 => 'field_app_boss_least_favorite',
      2 => 'field_app_class_contributes',
      3 => 'field_app_instances_experience',
      4 => 'field_app_raid_nights',
      5 => 'field_app_role_comfortable',
      6 => 'field_app_talents',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-raid-info field-group-fieldset',
      ),
    ),
  );
  $export['group_raid_info|node|guild_app|default'] = $field_group;

  return $export;
}
