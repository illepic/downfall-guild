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
  $field_group->identifier = 'group_app_group_character|node|guild_app|default';
  $field_group->group_name = 'group_app_group_character';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'guild_app';
  $field_group->mode = 'default';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Character',
    'weight' => '1',
    'children' => array(
      0 => 'field_app_class',
      1 => 'field_app_current_server',
      2 => 'field_app_race',
      3 => 'field_app_role',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'label' => 'Character',
      'instance_settings' => array(
        'required_fields' => 1,
        'classes' => 'group-app-group-character field-group-fieldset',
        'description' => '',
      ),
      'formatter' => 'collapsible',
    ),
  );
  $export['group_app_group_character|node|guild_app|default'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_app_group_character|node|guild_app|form';
  $field_group->group_name = 'group_app_group_character';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'guild_app';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Character',
    'weight' => '1',
    'children' => array(
      0 => 'field_app_char_name',
      1 => 'field_app_class',
      2 => 'field_app_current_server',
      3 => 'field_app_race',
      4 => 'field_app_role',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'label' => 'Character',
      'instance_settings' => array(
        'required_fields' => 1,
        'classes' => 'group-app-group-character field-group-fieldset',
        'description' => '',
      ),
      'formatter' => 'collapsible',
    ),
  );
  $export['group_app_group_character|node|guild_app|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_app_group_general|node|guild_app|default';
  $field_group->group_name = 'group_app_group_general';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'guild_app';
  $field_group->mode = 'default';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'General',
    'weight' => '2',
    'children' => array(
      0 => 'field_app_availability',
      1 => 'field_app_history',
      2 => 'field_app_led_to_guild',
      3 => 'field_app_state_of_class',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-app-group-general field-group-fieldset',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_app_group_general|node|guild_app|default'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_app_group_general|node|guild_app|form';
  $field_group->group_name = 'group_app_group_general';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'guild_app';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'General',
    'weight' => '2',
    'children' => array(
      0 => 'field_app_history',
      1 => 'field_app_led_to_guild',
      2 => 'field_app_state_of_class',
      3 => 'field_app_availability',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-app-group-general field-group-fieldset',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_app_group_general|node|guild_app|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_app_group_personal|node|guild_app|default';
  $field_group->group_name = 'group_app_group_personal';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'guild_app';
  $field_group->mode = 'default';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Personal',
    'weight' => '6',
    'children' => array(
      0 => 'field_app_language',
      1 => 'field_app_timezone',
      2 => 'field_app_yourself',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-app-group-personal field-group-fieldset',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_app_group_personal|node|guild_app|default'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_app_group_personal|node|guild_app|form';
  $field_group->group_name = 'group_app_group_personal';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'guild_app';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Personal',
    'weight' => '6',
    'children' => array(
      0 => 'field_app_language',
      1 => 'field_app_timezone',
      2 => 'field_app_yourself',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-app-group-personal field-group-fieldset',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_app_group_personal|node|guild_app|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_app_group_pve|node|guild_app|default';
  $field_group->group_name = 'group_app_group_pve';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'guild_app';
  $field_group->mode = 'default';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'PvE',
    'weight' => '4',
    'children' => array(
      0 => 'field_app_boss_encounters',
      1 => 'field_app_playstyle',
      2 => 'field_app_raid_experience',
      3 => 'field_app_specializations',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-app-group-pve field-group-fieldset',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_app_group_pve|node|guild_app|default'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_app_group_pve|node|guild_app|form';
  $field_group->group_name = 'group_app_group_pve';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'guild_app';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'PvE',
    'weight' => '4',
    'children' => array(
      0 => 'field_app_boss_encounters',
      1 => 'field_app_playstyle',
      2 => 'field_app_raid_experience',
      3 => 'field_app_specializations',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-app-group-pve field-group-fieldset',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_app_group_pve|node|guild_app|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_app_group_pvp|node|guild_app|default';
  $field_group->group_name = 'group_app_group_pvp';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'guild_app';
  $field_group->mode = 'default';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'PvP',
    'weight' => '5',
    'children' => array(
      0 => 'field_app_pvp_experience',
      1 => 'field_app_pvp_focus',
      2 => 'field_app_rated_bgs',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-app-group-pvp field-group-fieldset',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_app_group_pvp|node|guild_app|default'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_app_group_pvp|node|guild_app|form';
  $field_group->group_name = 'group_app_group_pvp';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'guild_app';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'PvP',
    'weight' => '5',
    'children' => array(
      0 => 'field_app_pvp_experience',
      1 => 'field_app_pvp_focus',
      2 => 'field_app_rated_bgs',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-app-group-pvp field-group-fieldset',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_app_group_pvp|node|guild_app|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_app_group_ui|node|guild_app|default';
  $field_group->group_name = 'group_app_group_ui';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'guild_app';
  $field_group->mode = 'default';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'UI',
    'weight' => '3',
    'children' => array(
      0 => 'field_app_addons',
      1 => 'field_app_field_like_your_ui',
      2 => 'field_app_ui_media',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-app-group-ui field-group-fieldset',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_app_group_ui|node|guild_app|default'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_app_group_ui|node|guild_app|form';
  $field_group->group_name = 'group_app_group_ui';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'guild_app';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'UI',
    'weight' => '3',
    'children' => array(
      0 => 'field_app_addons',
      1 => 'field_app_field_like_your_ui',
      2 => 'field_app_ui_media',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-app-group-ui field-group-fieldset',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_app_group_ui|node|guild_app|form'] = $field_group;

  return $export;
}
