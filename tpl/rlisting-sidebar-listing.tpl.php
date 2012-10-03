<?php

?>
<div class="rlisting-sidebar-listing clearfix"> 
  <div class="sidebar-title"><?php echo $title; ?></div>
  <div class="sidebar-image"><?php echo $image; ?></div>
  <div class="sidebar-info">
      <div class="info-price"><?php echo $price; ?></div>
      <?php if (!empty($building_type)): ?>
        <div class="info-building-type">
          <?php echo $building_type;?>
        </div>
      <?php endif; ?>
      <?php if (!empty($bedroom)): ?>
        <div class="info-bedroom">
          <span><?php echo t('Bed'); ?>: </span><?php echo $bedroom;?>
        </div>
      <?php endif; ?>
      <?php if (!empty($bathroom)): ?>
        <div class="info-bathroom">
          <span><?php echo t('Bath'); ?>: </span><?php echo $bathroom;?>
        </div>
      <?php endif; ?>
  </div>
</div>
