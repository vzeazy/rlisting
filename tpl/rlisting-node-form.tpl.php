<?php
/**
 * @file
 *  template file for rlisting_node_form -- see rlisting.theme.inc
 */

?>

<div class="rlisting-form-wrapper">
  <div class="header-wrapper"></div>
    <div id="rlisting-tabs">
    <ul>
      <li><a href="#tabs-listing">Listing Info</a></li>
      <li><a href="#tabs-location">Location</a></li>
      <li><a href="#tabs-details">Listing Details</a></li>
      <li><a href="#tabs-images">Images & Videos</a></li>
      <li><a href="#tabs-features">Features</a></li>
    </ul>

    <div id="tabs-listing">
      <?php echo $taxonomy_listing_tag; ?>
      <?php echo $rlisting_listing_type; ?>
      <?php echo $rlisting_building_type; ?>
      <?php echo $title; ?>
      <?php echo $body; ?>
    </div>
    <div id="tabs-location">
      <?php echo $rlisting_location; ?>
    </div>
    <div id="tabs-details">
      <?php echo $rlisting_mls; ?>
      <?php echo $rlisting_price; ?>
      <?php echo $rlisting_bedroom; ?>
      <?php echo $rlisting_bathroom; ?>
      <?php echo $rlisting_yearbuilt; ?>
      <?php echo $rlisting_floorsize; ?>
      <?php echo $rlisting_lotsize; ?>
      <?php echo $rlisting_maintenance_fee; ?>
    </div>
    <div id="tabs-images">
      <div class="video"><?php echo $rlisting_video; ?></div>
      <div class="photos"><?php echo $rlisting_photos; ?></div>
    </div>
    <div id="tabs-features">
      <?php echo $rlisting_features; ?>
    </div>
      <?php echo $rest_of_form; ?>
  </div>
</div>
