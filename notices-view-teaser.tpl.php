<div class="notice <?php print $zebra; ?><?php if ($notice->new) { print " notice-new";}?>" id="notice-<?php print $notice->noticeid; ?>">
    <div class="date">
      <?php print $timeago; ?>
    </div>
    <div class="picture"><img src="/<?php print $picture?>"> </div>
    <div class="message">
      <?php if ($notice->new) : ?>
        <span class="new"><?php print t('new');?></span>
      <?php endif ?>
      <?php print $content; ?>
    </div>
    <?php if ( isset($links)) : ?>
       <?php print $links ?>
    <?php endif ?>
  <div class="clear-both bottom-border"></div>
</div>