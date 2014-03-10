  <div class="node<?php if ($sticky) { print " sticky"; } ?><?php if (!$status) { print " node-unpublished"; } ?>">
    <?php if ($picture) {
      print $picture;
    }?>
    <?php if ($page == 0) { ?><h2 class="nodeTitle"><a href="<?php print $node_url?>"><?php print $title?></a></h2><?php }; ?>
    
	<?php if (!$teaser): ?>
	<?php if ($submitted): ?>
      <div class="metanode"><p><?php print t('By ') .'<span class="author">'. theme('username', $node).'</span>' . t(' - Posted on ') . '<span class="date">'.format_date($node->created, 'custom', "d F Y").'</span>'; ?></p>
	  

	  
	  </div> 
    <?php endif; ?>
    <?php endif; ?>
    
    <div class="content"><?php print $content?></div>
    
    
    <?php if (!$teaser): ?>
    <?php if ($links) { ?><div class="links"><?php print $links?></div><?php }; ?>
    <?php endif; ?>
    
    <?php if ($teaser): ?>
    <?php if ($links) { ?><div class="linksteaser"><div class="links"><?php print $links?></div></div><?php }; ?>
    <?php endif; ?>
    
    
    <?php if (!$teaser): ?>
    <?php if ($terms) { ?><div class="taxonomy"><span>Tags</span> <?php print $terms?></div><?php } ?>
    <?php endif; ?>
    
     

    
    
    
    
    
  </div>
