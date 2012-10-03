<?php
/**
 * @file
 * Ajax callback functions
 */


/**
 * Searches for listing via ajax form -- see maplisting.js
 */
function rlisting_ajax_markers() {
  $post = (object) $_POST;
  $post->max_price = $post->map_max_price;
  $post->min_price = $post->map_min_price;

  $query = rlisting_search_query($post, TRUE, 10);
  $result = $query->execute();

  $per_page =  variable_get('rlisting_ajax_per_page', 10);
  $markers = array();
  $marker_count =  0;
  $pager_cnt = 1;
  foreach($result as $record) {
    $node = node_load($record->nid);
    $marker_content = theme('rlisting_marker_content', array('node' => $node, 'map' => TRUE));
    if (location_has_coordinates($node->rlisting_location['und'][0])) {
      $markers[] = array(
        'lat' => $node->rlisting_location['und'][0]['latitude'],
        'lon' => $node->rlisting_location['und'][0]['longitude'],
        'text' => $marker_content,
      );

      $data .= '
        <div class="map-listing-item-wrapper" >
        <div class="map-listing-item" id="' . $node->nid . '" count="' . $marker_count . '">
          ' . $marker_content . '
        </div>
        </div>
      ';
      if ($pager_cnt % $per_page == 0){
        $sidebar .= '<div class="pager">' . $data . '</div>';
        $data = '';
      };
      $pager_cnt++;

      $marker_count++; // must be placed after sidebar
    };
  };
  
  if ($data) {
    $sidebar .= '<div class="pager">' . $data . '</div>';
  };

  print drupal_json_encode(
    array(
      'status' => TRUE,
      'markers' => $markers,
      'sidebar' => '<div id="pager">'. $sidebar.'</div>',
    )
  );
  exit();
};
