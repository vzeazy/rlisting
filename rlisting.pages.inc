<?php
/**
 * @file
 *  page functions for rListing
 */

/**
 * Google maps show all the listings
 */
function rlisting_map() {

  drupal_add_js(drupal_get_path('module', 'rlisting') . '/js/maplisting.js');
  drupal_add_js(drupal_get_path('module', 'rlisting') . '/js/jquery.pager.js');

  
  $output['map_form'] = drupal_get_form('rlisting_map_form');

  $query = db_select('node', 'n');
  $query->fields('n', array('nid'));
  $query->condition('n.type', 'rlisting');
  $query->condition('n.status', 1);
  $result = $query->execute();

  $nodes = array();
  foreach($result as $record) {
    $temp_node = node_load($record->nid);
    $node = new stdClass();
    $node->nid = $temp_node->nid;
    $node->title = $temp_node->title;
    $node->rlisting_price = $temp_node->rlisting_price;
    $node->rlisting_bedroom = $temp_node->rlisting_bedroom;
    $node->rlisting_bathroom = $temp_node->rlisting_bathroom;
    $node->rlisting_yearbuilt = $temp_node->rlisting_yearbuilt;
    $node->rlisting_location = $temp_node->rlisting_location;
    $node->rlisting_building_type = $temp_node->rlisting_building_type;
    $node->body = $temp_node->body;
    $node->rlisting_photos['und'][0] = $temp_node->rlisting_photos['und'][0];
  
    $nodes[$record->nid] = $node;

  };

  $markertypes = variable_get('gmap_node_makers', array());
  $markername = isset($markertypes['rlisting']) ? $markertypes['rlisting'] : 'drupal';
  
  $per_page =  variable_get('rlisting_ajax_per_page', 10);
  $data = $sidebar = '';
  $pager_cnt = $marker_cnt = 0;
  foreach ($nodes as $nid => $node) {
    $loc = $node->rlisting_location['und'][0];
    if (location_has_coordinates($loc)) {
      // this node has a location
      $markertitle = $node->title;
      if (!empty($loc['name'])) {
        $markertitle = $loc['name'];
      }; 
      $markers[] = array(
        'latitude' => $loc['latitude'],
        'longitude' => $loc['longitude'],
        'text' => theme('rlisting_marker_content', array('node' => $node, 'map' => TRUE)),
        'offset' => -1,
        'opts' => array('title' => $markertitle),
      );
      $data .= '
        <div class="map-listing-item-wrapper">
        <div class="map-listing-item" id="' . $node->nid . '" count="' . $marker_cnt . '">
          ' . theme('rlisting_marker_content', array('node' => $node, 'map' => FALSE)) . '
        </div>
        </div>
      ';
      if ($pager_cnt % $per_page == 0) {
        $sidebar .= '<div class="pager">' . $data . '</div>';
        $data = '';
      };
      $pager_cnt++;
      $marker_cnt++;
    };
  };
  if ($data) {
    $sidebar .= '<div class="pager">' . $data . '</div>';
  };

  // prepare the markers for gmap
  $map = '';
  if (!empty($markers)) {
    $map['maptype'] = 'Map';
    $map['latitude'] = $markers[0]['latitude'];
    $map['longitude'] = $markers[0]['longitude'];
    $map['controltype'] = 'Large';
    $map['mtc'] = 'standard';
    $map['markers'] = $markers;
    $map['id'] = 'maplisting';
    $map['width'] = '600px';
    $map['height'] = '500px';
    
    $element = array (
      '#type' => 'gmap',
      '#gmap_settings' => $map,
    );
    $map = drupal_render($element);
  };
  $map_html = '
    <div class="clear clear-block"></div>
    <div id="map-side">
      ' . $map  . ' 
    </div>    
    <div id="listing-side">
      <div id="pager"> 
        ' . $sidebar . '
      </div>
      <div class="clear clear-block"></div>
    </div>
    <div class="clear clear-block"></div>
    <div id="mapsearch">
    </div>
  ';

  $output['map'] = array(
    '#markup' => $map_html,
    '#weight' => 10,
  );


  return $output;
};

/**
 * browse Result page, normally from the sideblock search form.
 */
function rlisting_result($result = NULL) {

  if ($result == 'all') {
    // somebody clicked on the menu link - so by default, display all listings.
    $post = (object) array();
  }
  else {
    if(!empty($_SESSION['rlisting_browse'])) {
      $post = $_SESSION['rlisting_browse'];
    }
    else {
      $post = (object) array();
    };
  };

  $query = rlisting_search_query($post, TRUE, 40);

  $result = $query->execute();

  $allowed_values = list_allowed_values(field_info_field('rlisting_building_type'));
  $rows = array();
  foreach($result as $node) {
    $price = theme('rlisting_format_price', array('price' => $node->rlisting_price_value));
    $price = $price;
    $rows[] = array(
      array('data' => theme('rlisting_search_result', array('node' => $node))),
      array('data' => $allowed_values[$node->rlisting_building_type_value]),
      array('data' => $node->rlisting_bedroom_value),
      array('data' => $node->rlisting_bathroom_value),
      array('data' => $price),
    );
  };

  $output = array(
    'listing' => array(
      '#theme' => 'table',
      '#header' => rlisting_search_header(),
      '#rows' => $rows,
      '#empty' => t('No Listing Found'),
    ),
    'listing_pager' => array(
      '#theme' => 'pager',
      '#weight' => 10
    ),
  ); 

  return $output;
};
