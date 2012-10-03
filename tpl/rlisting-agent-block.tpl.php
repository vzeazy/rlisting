<?php
/** 
 * @file
 * theme file for agent profile block . See rlisting.theme.inc
 */
?>

<div class="rlisting-agent-wrapper">
  <?php if (!empty($agent_name)): ?>
  <div class="agent-name"><?php echo $agent_name; ?></div>
  <?php endif; ?>
  <?php if (!empty($agent_image)): ?>
  <div class="agent-image"><?php echo $agent_image; ?></div>
  <?php endif; ?>

  <div class="agent-info-wrapper">

    <?php if (!empty($agent_phone)): ?>
    <div class="label">Phone:</div><div class="agent-phone"><?php echo $agent_phone; ?></div>
    <?php endif; ?>
    <?php if (!empty($agent_fax)): ?>
    <div class="label">Fax:</div><div class="agent-fax"><?php echo $agent_fax; ?></div>
    <?php endif; ?>
    
  </div>
  <div class="agent-contact">
    <?php echo $agent_contact; ?> 
  </div>

  <div class="company-wrapper">
    <?php if (!empty($company_name)): ?>
    <div class="company-name"><?php echo $company_name; ?></div>
    <?php endif; ?>

    <?php if (!empty($company_logo)): ?>
    <div class="company-image"><?php echo $company_logo; ?></div>
    <?php endif; ?>

    <div class="company-info-wrapper">
      <?php if (!empty($company_phone)): ?>
      <div class="label">Phone:</div><div class="company-phone"><?php echo $company_phone; ?></div>
      <?php endif; ?>
      <?php if (!empty($company_fax)): ?>
      <div class="label">Fax:</div><div class="company-fax"><?php echo $company_fax; ?></div>
      <?php endif; ?>

      <?php if (!empty($company_website)): ?>
      <div class="agent-website"><?php echo $company_website; ?></div>
      <?php endif; ?>

    </div>

  </div>


</div>
