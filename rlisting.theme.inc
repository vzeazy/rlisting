<?php
/**
 * @file
 * Theme functions for rlisting
 */


/**
 * see rlisting-user-block.tpl.php
 */
function template_preprocess_rlisting_agent_block(&$variables) {

  $account  = $variables['user'];
  if (!empty($account->picture->uri)) {
    $args = array(
      'style_name' => 'rlisting-profile',
      'path' => $account->picture->uri,
      'height' => '',
      'width' => '',
    );
    $variables['agent_image'] = l(theme_image_style($args),'user/' . $account->uid, array('html' => TRUE));
  };

  $items = field_get_items('user', $account, 'field_agent_name');
  $variables['agent_name'] = $items[0]['safe_value'];

  $items = field_get_items('user', $account, 'field_agent_phone');
  $variables['agent_phone'] = $items[0]['safe_value'];

  $items = field_get_items('user', $account, 'field_agent_fax');
  $variables['agent_fax'] = $items[0]['safe_value'];

  $variables['agent_contact'] = l(t('Contact Realtor'), 'content/contact-realtor');

  // setup company info.
  if ($account->field_company_logo['und'][0]['uri']) {
    $args = array(
      'style_name' => 'rlisting-mini',
      'path' => $account->field_company_logo['und'][0]['uri'],
      'height' => $account->field_company_logo['und'][0]['height'],
      'width' => $account->field_company_logo['und'][0]['width'],
    );
    $variables['company_logo'] = theme_image_style($args);
  };

  $items = field_get_items('user', $account, 'field_company_name');
  $variables['company_name'] = $items[0]['safe_value'];

  $items = field_get_items('user', $account, 'field_company_phone');
  $variables['company_phone'] = $items[0]['safe_value'];

  $items = field_get_items('user', $account, 'field_company_fax');
  $variables['company_fax'] = $items[0]['safe_value'];

  $items = field_get_items('user', $account, 'field_company_website');
  $variables['company_website'] = $items[0]['safe_value'];

  $variables['company_website'] = l(t('Visit Office Website'), $variables['company_website']);

}
/**
 * see rlisting-sidebar-listing.tpl.php
 */
function template_preprocess_rlisting_sidebar_listing(&$variables) {

  $node  = $variables['node'];

  if (!empty($node->street)) {
    $variables['title'] = $node->street;
  }
  else {
    $variables['title'] = $node->rlisting_location['und'][0]['street'];
  }
  $variables['title'] = l($variables['title'], 'node/' . $node->nid);

  if (!empty($node->uri)) {
    $image_path = $node->uri;
  }
  elseif (!empty($node->rlisting_photos['und'][0]['uri'])) {
    $image_path = $node->rlisting_photos['und'][0]['uri'];
  }
  else {
    $image_path = '';
  };

  if (!empty($image_path)) {
    $args = array(
      'style_name' => 'rlisting-thumbnail',
      'path' => $image_path,
      'width' => '',
      'height' => '',
    );
    $variables['image'] = l(theme_image_style($args), 'node/' . $node->nid, array('html' => TRUE));
  }
  else {
    $variables['image'] = '';
  };

  if (!empty($node->rlisting_price_value)) {
    $variables['price'] =  theme('rlisting_format_price', array('price' => $node->rlisting_price_value));
  }
  else {
    $variables['price'] =  theme('rlisting_format_price', array('price' => $node->rlisting_price['und'][0]['value']));
  }

  $variables['bathroom'] = (!empty($node->rlisting_bathroom_value)) ? $node->rlisting_bathroom_value : $node->rlisting_bathroom['und'][0]['value']; ;
  $variables['bedroom'] = (!empty($node->rlisting_bedroom_value)) ? $node->rlisting_bedroom_value : $node->rlisting_bedroom['und'][0]['value']; ;

  $allowed_values = list_allowed_values(field_info_field('rlisting_building_type'));
  if (!empty($node->rlisting_building_type_value)) {
    $building_type = $allowed_values[$node->rlisting_building_type_value];
  }
  else {
    $building_type = $allowed_values[$node->rlisting_building_type['und'][0]['value']];
  }
  $variables['building_type'] = substr($building_type, 0, 9);

  if (strlen($building_type) > 9 )  {
    $variables['building_type'] .= ' ...' ;
  };

};


/**
 */
function theme_rlisting_format_price(&$variables) {
  $price = $variables['price'];

  $price_info = field_info_instance('node','rlisting_price','rlisting');

  return $price_info['settings']['prefix'] .
     number_format($price, 
    $price_info['display']['default']['settings']['scale'],
    $price_info['display']['default']['settings']['decimal_separator'],
    $price_info['display']['default']['settings']['thousand_separator']);

};

/**
 * format the listing title
 */
function theme_rlisting_listing_title(&$variables) {
  $node  = $variables['node'];
  if (empty($variables['link'])) {
    $link  = FALSE;
  } 
  else {
    $link  = $variables['link'];
  };

  $address_title = 
      $node->rlisting_location['und'][0]['street'] . ' ' .
      $node->rlisting_location['und'][0]['city'];

  if ($link) {
    $address_title = l($address_title, 'node/' . $node->nid);
  };

  return $address_title;

}

/**
 * gmap marker content
 */
function template_preprocess_rlisting_marker_content(&$variables) {

  $node  = $variables['node'];
  if (!empty($node->rlisting_photos['und'][0]['uri'])) {
    $arg = array(
      'style_name' => 'rlisting-mini',
      'path' => $node->rlisting_photos['und'][0]['uri'],
      'width' => $node->rlisting_photos['und'][0]['width'],
      'height' => $node->rlisting_photos['und'][0]['height'],
    );
    $variables['image'] = l(theme_image_style($arg), 'node/' . $node->nid, array('html' => TRUE));

  }
  else {
    $variables['image'] = '' ; 
  };

  $variables['title'] =  theme('rlisting_listing_title', array('node' => $node));
  $variables['price'] =  theme('rlisting_format_price', array('price' => $node->rlisting_price['und'][0]['value']));
  $variables['bedroom'] = $node->rlisting_bedroom['und'][0]['value'];
  $variables['bathroom'] = $node->rlisting_bathroom['und'][0]['value'];
  $variables['year_built'] = $node->rlisting_yearbuilt['und'][0]['value'];



  $allowed_values = list_allowed_values(field_info_field('rlisting_building_type'));
  $variables['building_type'] = $allowed_values[$node->rlisting_building_type['und'][0]['value']];

  $variables['node_url'] =  'node/' . $node->nid;
  if ($variables['map']) {
   $variables['description'] =  substr(strip_tags($node->body['und'][0]['value']), 0, 40);
  }
  else {
   $variables['description'] =  '';
  }

};

/**
 */
function template_preprocess_rlisting_search_result(&$variables) {

  $node = $variables['node'];

  if (!empty($node->vid)) {
    // full node load
    $node->uri = $node->rlisting_photos['und'][0]['uri'];
    $node->body_value = $node->body['und'][0]['value'];
    $node->street = $node->rlisting_location['und'][0]['street'];
    $node->city = $node->rlisting_location['und'][0]['city'];
  };


  if (!empty($node->uri)) {
    $arg = array(
      'style_name' => 'thumbnail',
      'path' => $node->uri,
      'width' => NULL,
      'height' => NULL,
    );
    $variables['image'] = l(theme_image_style($arg), 'node/' . $node->nid, array('html' => TRUE));
  };

  $variables['title'] = $node->title;
  $variables['body'] = substr(strip_tags($node->body_value), 0, 160);
  $variables['street'] = $node->street;
  $variables['city'] = $node->city;
  $variables['address'] = l($node->street . ' ' . $node->city, 'node/' . $node->nid);
  
  
};

/**
 * Preprocessor for rlisting teaserview
 */
function template_preprocess_rlisting_teaserview(&$variables) {

  $node = $variables['node'];

  if (!empty($node->rlisting_photos['und'][0]['uri'])) {
    $args = array(
      'style_name' => 'rlisting-teaser',
      'path' => $node->rlisting_photos['und'][0]['uri'],
      'width' => $node->rlisting_photos['und'][0]['width'],
      'height' => $node->rlisting_photos['und'][0]['height'],
    );
    $variables['image'] = l(theme_image_style($args), 'node/' . $node->nid, array('html' => TRUE));
  };

  $variables['price'] =  theme('rlisting_format_price', array('price' => $node->rlisting_price['und'][0]['value']));

  $variables['address_title'] = 
      $node->rlisting_location['und'][0]['street'] . ' ' .
      $node->rlisting_location['und'][0]['city'];

  $allowed_values = list_allowed_values(field_info_field('rlisting_building_type'));
  $variables['building_type'] = $allowed_values[$node->rlisting_building_type['und'][0]['value']];
  $allowed_values = list_allowed_values(field_info_field('rlisting_listing_type'));
  $variables['listing_type'] = $allowed_values[$node->rlisting_listing_type['und'][0]['value']];

  $variables['bedroom'] = $node->rlisting_bedroom['und'][0]['value'];
  $variables['bathroom'] = $node->rlisting_bathroom['und'][0]['value'];
  $variables['yearbuilt'] = $node->rlisting_yearbuilt['und'][0]['value'];
  $variables['mls'] = $node->rlisting_mls['und'][0]['value'];
  $variables['body'] =  substr(strip_tags($node->body['und'][0]['value']), 0, 300) . ' ...';
}
/**
 * Preprocessor for rlisting fullview
 */
function template_preprocess_rlisting_fullview(&$variables) {

  $node = $variables['node'];

  drupal_add_library('system', 'ui.tabs');
  drupal_add_js('    
    (function($){
        $(document).ready(function() {            
          $("#fullview-tabs").tabs({
            fx: { opacity: \'toggle\' }            
          });
        });    
    })(jQuery);
  ', 'inline');
  
  $items = field_get_items('node', $node, 'rlisting_location');
  $variables['address_title'] = $items[0]['street'] . ' ' . $items[0]['city'];

  $variables['field_listing_category'] = render($node->content['field_listing_category']);
  $variables['body'] = render($node->content['body']);
  $variables['rlisting_price'] = render($node->content['rlisting_price']);
  $variables['rlisting_maintenance_fee'] = render($node->content['rlisting_maintenance_fee']);
  $variables['rlisting_mls'] = render($node->content['rlisting_mls']);
  $variables['rlisting_bedroom'] = render($node->content['rlisting_bedroom']);
  $variables['rlisting_bathroom'] = render($node->content['rlisting_bathroom']);
  $variables['rlisting_yearbuilt'] = render($node->content['rlisting_yearbuilt']);
  $variables['rlisting_floorsize'] = render($node->content['rlisting_floorsize']);
  $variables['rlisting_lotsize'] = render($node->content['rlisting_lotsize']);
  $variables['rlisting_parking'] = render($node->content['rlisting_parking']);
  $variables['rlisting_location'] = render($node->content['rlisting_location']);
  $variables['rlisting_building_type'] = render($node->content['rlisting_building_type']);
  $variables['rlisting_listing_type'] = render($node->content['rlisting_listing_type']);
  $variables['rlisting_features'] = render($node->content['rlisting_features']);
  $variables['field_video'] = render($node->content['field_video']);
  $variables['rlisting_photos'] = render($node->content['rlisting_photos']);      

  $variables['rlisting_map'] = rlisting_api_map($node);

  // get open house
  $variables['rlisting_openhouse'] = theme('openhouse_listings', array('node' => $node));

  // form display;
  $display_form = drupal_get_form('rlisting_display_features_form', $node);
  $variables['features_form_display'] = render($display_form);

}
/**
 * Preprocessor for rlisting node
 */
function template_preprocess_rlisting_node_form(&$variables) {

  $form = $variables['form'];

  drupal_add_library('system', 'ui.tabs');
  drupal_add_js('    
    (function($){
        $(document).ready(function() {            
          $("#rlisting-tabs").tabs({
            fx: { opacity: \'toggle\' }            
          });
        });    
    })(jQuery);
  ', 'inline');


  $variables['title'] = drupal_render($form['title']);
  $variables['body'] = drupal_render($form['body']);
  $variables['rlisting_price'] = drupal_render($form['rlisting_price']);
  $variables['rlisting_maintenance_fee'] = drupal_render($form['rlisting_maintenance_fee']);
  $variables['rlisting_mls'] = drupal_render($form['rlisting_mls']);
  $variables['rlisting_bedroom'] = drupal_render($form['rlisting_bedroom']);
  $variables['rlisting_bathroom'] = drupal_render($form['rlisting_bathroom']);
  $variables['rlisting_yearbuilt'] = drupal_render($form['rlisting_yearbuilt']);
  $variables['rlisting_floorsize'] = drupal_render($form['rlisting_floorsize']);
  $variables['rlisting_lotsize'] = drupal_render($form['rlisting_lotsize']);
  $variables['rlisting_parking'] = drupal_render($form['rlisting_parking']);
  $variables['rlisting_location'] = drupal_render($form['rlisting_location']);
  $variables['rlisting_building_type'] = drupal_render($form['rlisting_building_type']);
  $variables['rlisting_listing_type'] = drupal_render($form['rlisting_listing_type']);
  $variables['rlisting_photos'] = drupal_render($form['rlisting_photos']);
  $variables['rlisting_video'] = drupal_render($form['field_video']);
  $variables['rlisting_features'] = drupal_render($form['rlisting_features']);
  $variables['taxonomy_listing_tag'] = drupal_render($form['taxonomy_listing_tag']);
  unset($form['#theme']);
  $variables['rest_of_form'] = drupal_render($form);
  
};
