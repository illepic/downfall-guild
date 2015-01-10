<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">


<head>

  <title><?php print $head_title ?></title>
  <?php print $head ?>
  <?php print $styles ?>
  <?php print $scripts ?>
</head>


<body class="k2 flex">

  <div id="utilities">
  <?php print $search_box ?>
  
  <?php if (isset($primary_links)) : ?>
  <?php print '<div id="plinks">'; ?>
          <?php print theme('links', $primary_links, array('class' => 'links primary-links')) ?>
          <?php print '</div>'; ?>
        <?php endif; ?>
  </div>


<div id="page">

  <div id="header">

<?php if ($site_name) : ?>
            <h1 class="sitetitle">
	      <a href="<?php print $base_path ?>" title="<?php print t('Home') ?>">
	        <?php print $site_name ?>
	      </a>
	    </h1>
	  <?php endif; ?>




  </div>
 <?php if ($site_slogan){?>
    <div id="slogan">
      <p><?php print $site_slogan ?></p>
        
    </div>
<?php } ?>
  <div class="content">
  
  
   <div id="primary" style=<?php print '"width:'.marinelli_width( $sidebar_right, $sidebar_left).'px;">' ?>
               <div class="singlepage">
	  <!--<div class="path"> <?php if ($breadcrumb) { ?><?php print $breadcrumb ?><?php } ?></div>-->

         <?php if ($title): print '<h2'. ($tabs ? ' class="with-tabs"' : '') .'>'. $title .'</h2>'; endif; ?>
          <?php if ($tabs): print '<div class="tabs">'.$tabs.'</div>'; endif; ?>
        <?php if ($help) { ?><div class="help"><?php print $help ?></div><?php } ?>
          <?php if ($messages) { ?><div class="messages"><?php print $messages ?></div><?php } ?>
<div class="drdot">
<hr />
</div>
          
 <?php print $content ?>
      </div>
      <hr />
      <!-- // itementry -->
    </div>
    <!-- //primary -->
    <hr />
   
   
   
        	<!-- sidebar_left -->
        <?php if ($sidebar_left) { ?>
          <div class="lsidebar">
            <?php print $sidebar_left ?>
          </div>
        <?php } ?>

   	<!-- sidebar_right -->
        <?php if ($sidebar_right) { ?>
          <div class="rsidebar">
 
            <?php print $sidebar_right ?>
         
          </div>
        <?php } ?>



 <div class="clear"></div>

  </div>
  <br class="clear" />
</div>
<!-- Close Page -->
<hr />
<div id="footer">
<?php print $footer_message ?>
</div>
<?php print $closure ?>
</body>
</html>