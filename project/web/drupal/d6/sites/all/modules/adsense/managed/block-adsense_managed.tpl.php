<div id="block-<?php print '-'. $block->delta; ?>" class="block">
<?php if ($block->subject): ?>
  <h2><?php print $block->subject ?></h2>
<?php endif;?>

  <div class="content">
    <?php print $block->content ?>
  </div>
</div>
