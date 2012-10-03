<?php
/** 
 * @file
 * Ajax callback functions
 */

/**
 * List all the openhouse for this particular listing.
 * 
 * @param $js
 *  is javascript enabled? 
 * @param $nid
 *  the listing id
 */
function openhouse_ajax_list($js = NULL, $nid = NULL) {

  $output = array();  
  if (!empty($nid)) { 
    ctools_include('modal');
    ctools_include('ajax');

    $listing = node_load($nid);

    $output[]['#markup'] = theme('rlisting_sidebar_listing', array('node' => $listing));
    $output[] = openhouse_api_listing_openhouse($listing->nid);

    $output[] = ctools_modal_command_display(t('Openhouse Listing'), $output);
    print ajax_render($output);
    exit; 
  }
  else {
    $output[]['#markup'] = t('Error');
    print ajax_render($output);
    exit; 
  }

};

/** 
 * Add new form called back ctools popup
 * 
 * @param $js
 *  flag to determine if javascript is working.
 *
 * @param $nid
 *  the listing id.
 */
function openhouse_ajax_add_new($js = NULL, $nid = NULL) {
  global $user;


  $node->id = $user->uid;
  $node->name = (isset($user->name) ? $user->name : '');
  $node->type = 'openhouse';
  $node->language = LANGUAGE_NONE;
  $node->listing_id = $nid;
  $node->status = TRUE;

  module_load_include('inc' , 'node', 'node.pages');
  if (!$js) {
    return drupal_get_form('openhouse_node_form', $node);
  }

  ctools_include('modal');
  ctools_include('ajax');
  $form= array();
  $form_state = array(
    'title' => t('New Openhouse'),
    'ajax' => TRUE,
    'node' => $node,
    'listing_id' => $nid,
  );
 
  $output = ctools_modal_form_wrapper('openhouse_node_form', $form_state);
  if (!empty($form_state['executed'])) {
    // just overwrite the form output if it was success ful
    $output = array();
    $output[] = ctools_ajax_command_reload();
  };

  print ajax_render($output);

  exit;

};
