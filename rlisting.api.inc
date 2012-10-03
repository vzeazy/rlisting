<?php
/**
 * @file
 * API functions for the rListing module.
 */

/**
 * Using this function to create the map so we can put a 
 * distance radius on the marker.
 * 
 * @param $node
 * - listing node.
 */
function rlisting_api_map($node) {

  $items = field_get_items('node', $node, 'rlisting_location');
  $center = $items[0];

  $markertitle = $node->title;
  if (!empty($center['name'])) {
    $markertitle = $center['name'];
  };
  $markers[] = array(
    'latitude' => $center['latitude'],
    'longitude' => $center['longitude'],
    'text' => theme('rlisting_marker_content', array('node' => $node, 'map' => TRUE)),
    'offset' => -1,
    'opts' => array('title' => $markertitle),
  );

    $map['maptype'] = 'Map';
    $map['latitude'] = $center['latitude'];
    $map['longitude'] = $center['longitude'];
    $map['controltype'] = 'Large';
    $map['mtc'] = 'standard';
    $map['markers'] = $markers;
    $map['id'] = 'maplisting';
    $map['width'] = '620px';
    $map['height'] = '500px';
    $map['shapes'] = array(
      array(
        'type' => 'circle',
        'center' => array($center['latitude'], $center['longitude']),
        'radius' => 1,
        'style' => array('ff0000', 1, 50, '00ff00', 15),
      ),
    );


    $element = array (
      '#type' => 'gmap',
      '#gmap_settings' => $map,
    );
    $map = drupal_render($element);


  $map_html = '
    <div class="clear clear-block"></div>
    <div id="map-side">
      ' . $map  . ' 
    </div>    
    <div class="clear clear-block"></div>
  ';


  return $map_html;
};



/** 
 * Sidebar random listing query .
 * 
 * @param $limit
 * Number of records to return.
 * 
 * @return 
 * SelectQuery object for the active database. 
 * 
 * This query does a similar listing query. Using price , bed (+/-1) and building type.
 */
function rlisting_api_sidebar_query($limit = 4, $node) {
  global $language;

  // setup params 
  if (!empty($node->rlisting_price)) {
    $price_up = $node->rlisting_price['und'][0]['value'] + 100000; 
    $price_down = $node->rlisting_price['und'][0]['value'] - 100000; 
    $building_type = $node->rlisting_building_type['und'][0]['value'];
    $bedrooms = $node->rlisting_bedroom['und'][0]['value'];
  } 
  else {
    $price_up =  '';
    $price_down = '';
    $building_type = '';
    $bedrooms = '';
  }

  // the URI file
  $sub_query = db_select('file_usage', 'f');
  $sub_query->join('file_managed', 'fm', 'f.fid = fm.fid');
  $sub_query->fields('f', array('id'));
  $sub_query->fields('fm', array('uri'));
  $sub_query->condition('f.type', 'node');
  $sub_query->groupBy('id');

  $query = db_select('node', 'n')->extend('PagerDefault');
  $query->leftJoin('node_revision','nv', 'n.nid = nv.nid');
  $query->leftJoin('field_data_rlisting_bedroom', 'fbed', 'n.nid = fbed.entity_id');
  $query->leftJoin('field_data_rlisting_bathroom', 'fbath', 'n.nid = fbath.entity_id');
  $query->leftJoin('field_data_rlisting_price', 'p', 'n.nid = p.entity_id');
  $query->leftJoin('field_data_rlisting_location', 'rl', 'n.nid = rl.entity_id');
  $query->leftJoin('field_data_rlisting_building_type', 'btype', 'n.nid = btype.entity_id');
  $query->leftJoin('location_instance', 'li', 'rl.rlisting_location_lid = li.lid');
  $query->leftJoin('location', 'l', 'l.lid = li.lid');
  $query->leftJoin($sub_query, 'file', 'file.id = n.nid');

  $query->fields('nv', array('nid', 'title', 'uid', 'timestamp'));
  $query->fields('p', array('rlisting_price_value'));
  $query->fields('fbath', array('rlisting_bathroom_value'));
  $query->fields('fbed', array('rlisting_bedroom_value'));
  $query->fields('btype', array('rlisting_building_type_value'));
  $query->fields('file', array('uri'));
  $query->fields('l', array('street','city'));

  $query->condition('n.type', 'rlisting');
  $query->condition('n.status', 1);
  $query->condition('n.nid', $node->nid, '<>');
  $query->condition('fbed.rlisting_bedroom_value', $bedrooms);
  $query->condition('btype.rlisting_building_type_value', $building_type);
  $query->condition('p.rlisting_price_value',array($price_down, $price_up), 'BETWEEN');
  $query->condition('n.language', array($language->language, LANGUAGE_NONE), 'IN');
  $query->orderRandom();
  $query->limit($limit);

  return $query; 

};

/**
 * Return the table header
 */
function rlisting_search_header() {

  $header[] = array('data' => t('Listing'));
  $header[] = array('data' => t('Type'), 'field' => 'btype.rlisting_building_type_value');
  $header[] = array('data' => t('Bed'), 'field' => 'fbed.rlisting_bedroom_value');
  $header[] = array('data' => t('Bath'), 'field' => 'fbath.rlisting_bathroom_value');
  $header[] = array('data' => t('Price'), 'field' => 'p.rlisting_price_value', 'sort' => 'asc');

  return $header;
};

/**
 * General search query
 * 
 * @param $post
 * An array of submitted form value.
 * array('listing_type', 'building_type', 'bedrooms', 'bathrooms', 'min_price', 'max_price');
 *
 * @param $pager
 * Boolean whether add a pager or not.
 * 
 * @param limit
 * If there's a pager, then how many per page?
 * 
 * @return
 * SelectQuery object for the active database.
 * 
 */
function rlisting_search_query($post = array(), $pager = FALSE, $limit = NULL) {
  global $language;

  $header = rlisting_search_header();

  $sub_query = db_select('file_usage', 'f');
  $sub_query->join('file_managed', 'fm', 'f.fid = fm.fid');
  $sub_query->fields('f', array('id'));
  $sub_query->fields('fm', array('uri'));
  $sub_query->condition('f.type', 'node');
  $sub_query->groupBy('id');

  $query = db_select('node', 'n')->extend('PagerDefault')->extend('TableSort');
  $query->leftJoin('node_revision','nv', 'n.nid = nv.nid');
  $query->leftJoin('field_data_rlisting_bedroom', 'fbed', 'n.nid = fbed.entity_id');
  $query->leftJoin('field_data_rlisting_bathroom', 'fbath', 'n.nid = fbath.entity_id');
  $query->leftJoin('field_data_rlisting_price', 'p', 'n.nid = p.entity_id');
  $query->leftJoin('field_data_rlisting_listing_type', 'ltype', 'n.nid = ltype.entity_id');
  $query->leftJoin('field_data_rlisting_building_type', 'btype', 'n.nid = btype.entity_id');
  $query->leftJoin('field_data_body', 'fbody', 'n.nid = fbody.entity_id');

  $query->leftJoin('field_data_rlisting_location', 'rl', 'n.nid = rl.entity_id');
  $query->leftJoin('location_instance', 'li', 'rl.rlisting_location_lid = li.lid');
  $query->leftJoin('location', 'l', 'l.lid = li.lid');
  $query->leftJoin($sub_query, 'file', 'file.id = n.nid');

  $query->fields('nv', array('nid', 'title', 'uid', 'timestamp'));
  $query->fields('p', array('rlisting_price_value'));
  $query->fields('fbath', array('rlisting_bathroom_value'));
  $query->fields('fbed', array('rlisting_bedroom_value'));
  $query->fields('btype', array('rlisting_building_type_value'));
  $query->fields('fbody', array('body_value'));
  $query->fields('file', array('uri'));
  $query->fields('l', array('street','city'));

  $query->condition('n.type', 'rlisting');
  $query->condition('n.status', 1);
  $query->condition('n.language', array($language->language, LANGUAGE_NONE), 'IN');

  if (!empty($post->listing_type)) {
    $query->condition('ltype.rlisting_listing_type_value', $post->listing_type, '=');
  };
  if (!empty($post->building_type)) {
    $query->condition('btype.rlisting_building_type_value', $post->building_type, '=');
  };
  if (!empty($post->bedrooms)) {
    $query->condition('fbed.rlisting_bedroom_value', $post->bedrooms, '>=');
  };
  if (!empty($post->bathrooms)) {
    $query->condition('fbath.rlisting_bathroom_value', $post->bathrooms, '>=');
  };
  if (!empty($post->max_price) && !empty($post->min_price)) {
    $query->condition('p.rlisting_price_value',array($post->min_price, $post->max_price ), 'BETWEEN');
  };


  if ($pager && $limit)  {
    $query->limit($limit);
  };

  $query->orderByHeader($header);


  return $query;  

};
