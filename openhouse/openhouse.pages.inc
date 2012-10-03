<?php
/** 
 * @file
 * Page functions for openhouse module.
 */

/**
 * menu callback to view the listing
 */
function openhouse_rlisting($openhouse_node) {

  // re-direct to listing page when user clicks on listing tab.
  drupal_goto('node/' . $openhouse_node->listing_id ) ;

};

/**
 * main openhouse entry form callback.
 */
function openhouse_add($listing_node) {
  global $user;


  include_once(drupal_get_path('module', 'node') . '/node.pages.inc');
  $type = 'openhouse';

  $output[]['#markup'] = theme('rlisting_sidebar_listing', array('node' => $listing_node));
  if (!empty($listing_node)) {
    $title = theme('rlisting_listing_title', array('node' => $listing_node));
    if (empty($form['title']['#default_value'])) {
      $form['title']['#default_value'] = strip_tags($title);
    };
    $output[] = openhouse_api_listing_openhouse($listing_node->nid);

  };


  $types = node_type_get_types(); 
  $node = (object) array('uid' => $user->uid, 'name' => (isset($user->name) ? $user->name : ''), 'type' => $type, 'language' => LANGUAGE_NONE);
  drupal_set_title(t('Create @name', array('@name' => $types[$type]->name)), PASS_THROUGH);

  if (user_access('create openhouse content', $user)) {
    $output[] = drupal_get_form($type . '_node_form', $node, $listing_node);
  }
  else {
    //$output .= '';
  };
  drupal_set_title(t('Open House for ') . '"' .  $listing_node->title . '"');

  return $output;

};
