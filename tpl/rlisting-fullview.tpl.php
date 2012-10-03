<?php
?>
    <div class="title"><h3><?php echo $address_title; ?></h3></div>
<div class="rlisting-photos"><?php echo $rlisting_photos; ?>
  <div class="clearfix"></div>
</div>
<div class="rlisting-details-wrapper">
    <div class="row-even building-type"><?php echo $rlisting_building_type; ?></div>
    <div class="row-odd price"><?php echo $rlisting_price; ?></div>
    <div class="row-even mls"><?php echo $rlisting_mls; ?></div>
    <div class="row-odd yearbuilt"><?php echo $rlisting_yearbuilt; ?></div>
    <div class="row-even bedroom"><?php echo $rlisting_bedroom; ?></div>
    <div class="row-odd bedroom"><?php echo $rlisting_bathroom; ?></div>
</div>
<div id="fullview-tabs">
  <ul>
    <li><a href="#tabs-overview">Overview</a></li>
    <li><a href="#tabs-details">Details</a></li>
    <li><a href="#tabs-features">Features</a></li>
    <li><a href="#tabs-openhouse">Openhouse</a></li>
  </ul>

  <div id="tabs-overview">
    <div class="title"><h3><?php echo $address_title; ?></h3></div>
    <div class="body"><?php echo $body; ?></div>
    <div class="location"><?php echo $rlisting_location; ?></div>
    <div class="rlisting-map"><?php echo $rlisting_map; ?></div>
  </div>
  <div id="tabs-details">
    <div class="price"><?php echo $rlisting_price; ?></div>
    <div class="maintenace-fee"><?php echo $rlisting_maintenance_fee; ?></div>
    <div class="mls"><?php echo $rlisting_mls; ?></div>
    <div class="bedroom"><?php echo $rlisting_bedroom; ?></div>
    <div class="bathroom"><?php echo $rlisting_bathroom; ?></div>
    <div class="yearbuilt"><?php echo $rlisting_yearbuilt; ?></div>
    <div class="lotsize"><?php echo $rlisting_lotsize; ?></div>
    <div class="floorsize"><?php echo $rlisting_floorsize; ?></div>
  </div>
  <div id="tabs-features">
    <div class="features"><?php echo $features_form_display; ?></div>
  </div>
  <div id="tabs-openhouse">
    <div class="openhouse"><?php echo $rlisting_openhouse; ?></div>
  </div>

</div>
