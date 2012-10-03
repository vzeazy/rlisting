<div class="rlisting-marker marker-<?php echo $node->nid;?>">

  <?php if($image):?>
  <div class="marker-title"><a href="<?php echo $node_url; ?>"><?php echo $title;?></a></div>
  <div class="image"><?php echo $image; ?></div>
  <?php endif; ?>
  <?php if($price):?>
  <div class="price"><?php echo $price; ?></div>
  <?php endif; ?>
  <?php if($description):?>
  <div class="description"><?php echo $description; ?></div>
  <?php endif; ?>
  <table>
    <thead>
      <tr>
        <?php if ($building_type): ?>
        <td></td>
        <?php endif; ?>
        <?php if ($year_built): ?>
        <td>Year</td>
        <?php endif; ?>
        <?php if ($bedroom): ?>
        <td>Beds</td>
        <?php endif; ?>
        <?php if ($bathroom): ?>
        <td>Bath</td>
        <?php endif; ?>
      </tr>
    </thead>
    <tr>
      <?php if ($building_type): ?>
      <td><div class="item building-type"><?php echo $building_type;?></div></td>
      <?php endif; ?>
      <?php if ($year_built): ?>
      <td><div class="item year_built"><?php echo $year_built;?></div></td>
      <?php endif; ?>
      <?php if ($bedroom): ?>
      <td><div class="item bedroom"><?php echo $bedroom;?></div></td>
      <?php endif; ?>
      <?php if ($bathroom): ?>
      <td><div class="item bathroom"><?php echo $bathroom;?></div></td>
      <?php endif; ?>
    </tr>
  </table>

</div>

