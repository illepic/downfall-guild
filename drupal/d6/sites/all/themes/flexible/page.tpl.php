<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN"
  "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<?php
	$thispage = $_SERVER['PHP_SELF'].'?'.$_SERVER['QUERY_STRING'];
	// get an id which uniquely identifies the site - database host_database_prefix
	global $db_url, $db_prefix;
	$themepath = drupal_get_path('theme', 'flexible');
	// set the defaults - ie no stylesheets
	$stylesheets['_default']['_default']='';
	$stylesheets['colour']['_default']='';
	$stylesheets['font']['_default']='';
	// scan the theme and site directory for more style sheets
	scan_stylesheets($themepath, $stylesheets);
	scan_stylesheets($themepath.'/'.$site_name, $stylesheets);
	// set the default user selections
	$selection['_default'] = '_default'; // this is the only possible choice for this one
	$selection['colour'] = '_default';
	$selection['font'] = '_default';
	// update the user's selections in user and session
	global $user;
	if ($_REQUEST['accessibility']) {
		// save data for logged on users
		if ($user->uid) {
			$options['flexibleaccessibility'] = array(
				'colour'=>$_REQUEST['colour'],
				'font'=>$_REQUEST['font'],
				'linear'=>$_REQUEST['linear']
			);
			user_save($user, $options);
			// save in current user object
			$user->flexibleaccessibility = array(
				'colour'=>$_REQUEST['colour'],
				'font'=>$_REQUEST['font'],
				'linear'=>$_REQUEST['linear']
			);
		}
		// save in session
		$_SESSION['flexibleaccessibility'] = array(
				'colour'=>$_REQUEST['colour'],
				'font'=>$_REQUEST['font'],
				'linear'=>$_REQUEST['linear']
			);
	}
	// load the users selections
	if ($user->uid and $user->flexibleaccessibility) {
		// if possible, get from user object
		$selection = array_merge($selection, $user->flexibleaccessibility);
	} elseif ($_SESSION['flexibleaccessibility']) {
		// otherwise try session object
		$selection = array_merge($selection, $_SESSION['flexibleaccessibility']);
	} else {
		// last resort for anonymous users is the request object
		if ($_REQUEST['colour']) {$selection['colour'] = $_REQUEST['colour'];}
		if ($_REQUEST['font']) {$selection['font'] = $_REQUEST['font'];}
		if ($_REQUEST['linear']) {$selection['linear'] = $_REQUEST['linear'];}
	}
	// how many columns 
	$cols = 1;
	if ($sidebar_left) {$cols++;}
	if ($sidebar_right) {$cols++;}
?>
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="<?php print $language ?>" lang="<?php print $language ?>">
	<head>
		<!-- site id = <?php print $site_name ?> -->
		<title><?php print $head_title; // if ($user->uid==1) {print ' '.$_SERVER["SERVER_ADDR"];} ?></title>
		<?php print $head ?>
		<?php print $styles ?>
		<?php foreach ($stylesheets['_default'] as $name=>$value) { ?>
			<style type="text/css" media="all">@import "<?php print base_path().$value; ?>";</style>
		<?php } ?>
		<?php if ($stylesheets['colour'][$selection['colour']]): ?>
			<style type="text/css" media="all">@import "<?php print base_path().$stylesheets['colour'][$selection['colour']]; ?>";</style>
		<?php endif; ?>
		<?php if ($stylesheets['font'][$selection['font']]): ?>
			<style type="text/css" media="all">@import "<?php print base_path().$stylesheets['font'][$selection['font']]; ?>";</style>
		<?php endif; ?>
		<?php print $scripts ?>
	</head>

	<body>
	<!-- ACCESSIBILITY LINKS, positioned off-page but "visible" to text readers -->
	<div id="access" class="<?php print $selection['linear'] ? 'linear' : 'tabular'; ?>">
		<?php 
			$skip_c = t('Skip to main content');
			$skip_n = t('Skip to site navigation');
			$skip_a = t('Skip to accessibility settings');
			$skip_s = t('Skip to search box');
			$skip_l = t('Skip to left sidebar');
			$skip_r = t('Skip to right sidebar');
			$skip_h = t('Home page');
			$skip_f = t('Frequently asked questions (FAQ)');
			$skip_ag = t('Accessibility guide');
			$skip_t = t('Terms and conditions');
		?>
		<a href="#skip_c" accesskey="S"><?php print $skip_c ?></a>
		<?php if (strpos($header.$sidebar_left.$content.$sidebar_right, '"skip_n"')): ?>
			- <a href="#skip_n" accesskey="3"><?php print $skip_n; ?></a>
		<?php endif; ?>
		- <a href="#skip_a"><?php print $skip_a ?></a>
		<?php global $search_block; if ($search_block): ?>
			- <a href="#skip_s" accesskey="4"><?php print $skip_s; ?></a>
		<?php endif; ?>
		<?php if ($sidebar_left): ?>
			- <a href="#skip_l"><?php print $skip_l; ?></a>
		<?php endif; ?>
		<?php if ($sidebar_right): ?>
			- <a href="#skip_r"><?php print $skip_r; ?></a>
		<?php endif; ?>
	</div>
	<a id="accessibilityguide" href="?q=_access_" accesskey="0"><?php print $skip_ag; ?></a>

<?php //Layout table or linear content
	if ($selection['linear']): ?>
<?php else: ?>
	<table class="layout"> <!-- sorry purists -->
<?php endif; ?>

	<!-- HEADER -->
<?php if ($selection['linear']): ?>
	<div id="header">
<?php else: ?>
	<tr><td id="header" colspan="<?php print $cols ?>"><div class=t><div class=b><div class=l><div class=r><div class=tl><div class=tr><div class=bl><div class=br><div class=inner>
<?php endif; ?>
		<?php if ($pre_header = theme_blocks('pre_header')): ?>
			<div id="pre-header"><?php print $pre_header; ?></div>
		<?php endif; ?>
		<?php
		// display header
		if ($logo || $site_name || $site_slogan) {
			print '<h1><a href="'. check_url($base_path) .'" title="'. $site_name .'">';
			if ($logo) {
				print '<img src="'. check_url($logo) .'" alt="'. $site_name .'" id="logo" />';
			}
			if ($site_name) {
				print '<div id="site_name">'.$site_name.'</div>';
			}
			if ($site_slogan) {
				print '<div id="site_slogan">'.$site_slogan.'</div>';
			}
			print '</a></h1>';
		}
		?>
		<div id="header-region" class="clear-block"><?php print $header; ?></div>
<?php if ($selection['linear']): ?>
	</div>
<?php else: ?>
	</div></div></div></div></div></div></div></div></div></td></tr>
<?php endif; ?>

<?php // Left sidebar goes before main content in tabular layout
	if (!$selection['linear']): ?>
	<tr>
	<!-- LEFT SIDEBAR -->
	<?php if ($sidebar_left): ?>
		<td id="sidebar-left" class="sidebar"><div class=t><div class=b><div class=l><div class=r><div class=tl><div class=tr><div class=bl><div class=br><div class=inner>

			<a id="skip_l" />
			<?php print $sidebar_left ?>
		</div></div></div></div></div></div></div></div></div></td>
	<?php endif; ?>
<?php endif; ?>

	<!-- MAIN CONTENT -->
<?php if ($selection['linear']): ?>
	<div id="content">
<?php else: ?>
	<td id="content"><div class=t><div class=b><div class=l><div class=r><div class=tl><div class=tr><div class=bl><div class=br><div class=inner>
<?php endif; ?>
		<?php if ($breadcrumb): print $breadcrumb; endif; ?>
		<a id="skip_c"></a>
		<?php if ($mission): print '<div id="mission">'. $mission .'</div>'; endif; ?>
		<?php if ($tabs): print '<div id="tabs-wrapper" class="clear-block">'; endif; ?>
		<?php if ($title): print '<h2'. ($tabs ? ' class="with-tabs"' : '') .'>'. $title .'</h2>'; endif; ?>
		<?php if ($tabs): print $tabs .'</div>'; endif; ?>
		<?php if (isset($tabs2)): print $tabs2; endif; ?>
		<?php if ($help): print $help; endif; ?>
		<?php if ($messages): print $messages; endif; ?>
		<?php print $content ?>
		<?php print $feed_icons ?>
<?php if ($selection['linear']): ?>
	</div>
<?php else: ?>
	</div></div></div></div></div></div></div></div></div></td>
<?php endif; ?>

<?php // Left sidebar goes after main content in tabular layout
	if ($selection['linear']): ?>
	<!-- LEFT SIDEBAR -->
	<?php if ($sidebar_left): ?>
		<div id="sidebar-left" class="sidebar">
			<a id="skip_l" />
			<?php print $sidebar_left ?>
		</div>
	<?php endif; ?>
<?php endif; ?>

	<!-- RIGHT SIDEBAR -->
	<?php if ($sidebar_right): ?>
		<?php if ($selection['linear']): ?>
			<div id="sidebar-right" class="sidebar">
				<a id="skip_r" />
				<?php print $sidebar_right ?>
			</div>
		<?php else: ?>
			<td id="sidebar-right" class="sidebar"><div class=t><div class=b><div class=l><div class=r><div class=tl><div class=tr><div class=bl><div class=br><div class=inner>
				<a id="skip_r" />
				<?php print $sidebar_right ?>
			</div></div></div></div></div></div></div></div></div></td>
		<?php endif; ?>
	<?php endif; ?>
	</tr>
	
	<!-- FOOTER -->
	<?php if ($selection['linear']): ?>
		<div id="footer" colspan="<?php print $cols ?>">
			<div id="footer_wrapper"><?php print $footer_message ?></div>
		</div>
	<?php else: ?>
		<tr><td id="footer" colspan="<?php print $cols ?>"><div class=t><div class=b><div class=l><div class=r><div class=tl><div class=tr><div class=bl><div class=br><div class=inner>
			<div id="footer_wrapper"><?php print $footer_message ?></div>
		</div></div></div></div></div></div></div></div></div></td></tr>
	<?php endif; ?>
	
	<!-- ACCESS SETTINGS -->
	<?php if ($selection['linear']): ?>
		<div id="accesssettings">
	<?php else: ?>
		<tr><td id="accesssettings" colspan="<?php print $cols ?>"><div class=t><div class=b><div class=l><div class=r><div class=tl><div class=tr><div class=bl><div class=br><div class=inner>
	<?php endif; ?>	
		<a id="skip_a" accesskey="6"></a>
		<h3><?php print t('Accessibility') ?></h3>
		<form method="post" action="<?php print $thispage ?>">
		<?php
			unset ($stylesheets['_default']);
			foreach ($stylesheets as $type=>$options) { ?>
				<?php print t($type); ?>
				<select name="<?php print $type ?>">
					<?php
						foreach ($options as $option_name=>$option_value) { ?>
							<option value="<?php print $option_name ?>" <?php ; print ($selection[$type] == $option_name) ? 'selected': '' ?>><?php print ($option_name == '_default') ? t('standard') : t($option_name) ?></option>
						<?php }
					?>
				</select>
			<?php }
		?>
		<input type="checkbox" name="linear" <?php print ($selection['linear']) ? ' checked=on ' : ''; ?> alt="<?php print t('Linear layout - more suited to braille, speech or text browsers'); ?>">&nbsp;<?php print t('Linear layout'); ?>
		<input type="submit" name="accessibility" value="<?php print t('Save accessibility settings'); ?>" alt="<?php print t('Click here to save changes to accessibility settings'); ?>">
		</form>
		<br /><a href="?q=_access_"><?php print $skip_ag; ?></a>
		- <a href='<?php print $_SERVER['PHP_SELF']; ?>' accesskey="1"><?php print $skip_h; ?></a>
		<?php if (strpos($sidebar_left.$content.$sidebar_right, '_faq_')): ?>
			- <a href="?q=_faq_" accesskey="5"><?php print $skip_f; ?></a>
		<?php endif; ?>
		<?php if (strpos($sidebar_left.$content.$sidebar_right, '_terms_')): ?>
			- <a href="?q=_terms_" accesskey="8"><?php print $skip_t; ?></a>
		<?php endif; ?>
	<?php if ($selection['linear']): ?>
		</div>
	<?php else: ?>
		</div></div></div></div></div></div></div></div></div></td></tr>
	</table>
	<?php endif; ?>

	<?php print $closure ?>

</html>
