<?php
/**
 * @file
 * downfall_migrate_feature.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function downfall_migrate_feature_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "ds" && $api == "ds") {
    return array("version" => "1");
  }
  if ($module == "field_group" && $api == "field_group") {
    return array("version" => "1");
  }
  if ($module == "file_entity" && $api == "file_default_displays") {
    return array("version" => "1");
  }
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_image_default_styles().
 */
function downfall_migrate_feature_image_default_styles() {
  $styles = array();

  // Exported image style: image_900.
  $styles['image_900'] = array(
    'name' => 'image_900',
    'label' => 'image_900',
    'effects' => array(
      1 => array(
        'label' => 'Scale',
        'help' => 'Scaling will maintain the aspect-ratio of the original image. If only a single dimension is specified, the other dimension will be calculated.',
        'effect callback' => 'image_scale_effect',
        'dimensions callback' => 'image_scale_dimensions',
        'form callback' => 'image_scale_form',
        'summary theme' => 'image_scale_summary',
        'module' => 'image',
        'name' => 'image_scale',
        'data' => array(
          'width' => 900,
          'height' => '',
          'upscale' => 0,
        ),
        'weight' => 1,
      ),
    ),
  );

  return $styles;
}

/**
 * Implements hook_node_info().
 */
function downfall_migrate_feature_node_info() {
  $items = array(
    'df_image' => array(
      'name' => t('Image'),
      'base' => 'node_content',
      'description' => t('Pictures, screenshots, etc.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
    'event' => array(
      'name' => t('Event'),
      'base' => 'node_content',
      'description' => t('An event - raid, real life, or otherwise - can be made using this.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
    'guild_app' => array(
      'name' => t('Guild Application'),
      'base' => 'node_content',
      'description' => t('This is what you use to apply to Downfall. Our recruitment process goes something like this: A) Register on the site B) Apply using this content type, C) Reply and keep up with the questions on the application, D) Wait, E) Run an instance/raid/BG with Df members a few times, F) Don\'t fuck up or be a douche, G) Wait some more, H) finally, when enough people request a person get ginvited an officer will pull them in. It\'s a long process. No, we don\'t care that you killed Sha of Fear in LFR.'),
      'has_title' => '1',
      'title_label' => t('Title of your guild application'),
      'help' => t('<p>Personality counts.  Brains count.  Spelling counts.  We need quality people, not loot-whoring, whiny, emo douchebags.  That said, please fill out the following fields to the best of your ability.  Once you submit your application, our guildies will add comments to it.  Please keep up with this app and respond to the feedback.  Most of your chances at an invite depend on your replies to the guildy comments.  Also, <a href="http://vgstrategies.about.com/od/pccheatsw/a/MB2-World-Of-Warcraft-Guide-Apply-for-Raiding-Guild.htm" target="_blank">read this</a>.  To get a feel for the kind of grilling you can expect from our members, look at some of <a href="http://www.downfallguild.org/apps/Open/all" target="_blank">the current open apps.</a>  To see what NOT to do, check our sample <a href="http://downfallguild.org/node/3212" target="_blank">What Not To Do App</a>.  Please do not app if you cannot take criticism.  Expect to explain yourself thoroughly. </p>

<p>Additional Note: We mean it when we say "spelling counts."  Put in the effort to do a good job and we\'ll put in the effort to give you meaningful feedback and a possible invite.  A great way to get your app immediately canned is to use "ur", "wut", "u" or any other internet shorthand.  We hold all our people to a higher standard, please be courteous and show us you can grasp the English language. </p>

<p>Does this seem like a lot of work?  Good.  Put in the time, we\'ll notice.  Please also join the <strong>/dfrecruit</strong> channel in-game.  This will give us a chance to actually, you know, talk to you!  Use that channel to get some groups formed with our guildies.</p>

<p>Downfall isn\'t just a guild, were a community of friends who meet both in game and in real life. If all you\'re interested in is a temporary place to hang your helm and get achievements and loot, please don\'t app. We\'re looking always to add not only raiders, but family members. That being said.......</p>
<ul>
<li>DO NOT APPLY if you are not fully enchanted, head to toe. Yes, even on that piece that you will "replace soon". No excuses, do not even apply unless you are fully enchanted.</li>
<li>DO NOT APPLY if you not fully gemmed.  Go gem it all, best gems possible.</li>
<li>DO NOT APPLY if you\'re a douchebag. Seriously, if you find that most people in your life hate you, don\'t apply to Downfall.</li>
<li>We expect you to know your class intimately.  You should have theorycrafting resources like elitistjerks.com and icy-veins.com bookmarked and read up frequently.</li>
</ul>
<p>This app is the best way we feel we can get to know people in a short period. Someone will undoubtedly comment on your app within the first day. Be open to constructive criticism and ready to talk about your class and how you play in full detail. </p>

<p><strong>IMPORTANT: If you don\'t check on your application at least once every couple of days, and post a response to the discussion on your application, it will be declined and closed in a very short period of time.</strong> We are looking for ACTIVE players who know how to use the tools provided them. If you demonstrate little activity on your app, it will be closed quickly.</p>'),
    ),
    'raid' => array(
      'name' => t('Raid Group'),
      'base' => 'node_content',
      'description' => t('Create a raid that gets its own section on the site. Members can subscribe to it and you, as the creator of the raid, can automatically or manually add members to it. Forum posts, images, events, videos, boss kills, news, etc can all be posted to this raid.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  return $items;
}
