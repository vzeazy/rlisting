<?php
/**
 * @file
 * API functions 
 */


/**
 * list all openhoue in a table for a given listing node.
 */
function openhouse_api_listing_openhouse($listing_id) {
  $tz = drupal_get_user_timezone();

  $admin = user_access('administer openhouse');

  $query = db_select('openhouse_listing', 'o');
  $query->fields('o', array('oid'));
  $query->condition('o.nid', $listing_id);

  $result = $query->execute();
  $rows = array();
  foreach($result as $record) {
    $node = node_load($record->oid); 


    //$start_timestamp = $node->start_date['und'][0]['value'];
    $start_date = format_date($node->open_date['und'][0]['value'], 'long');
    $end_date = format_date($node->open_date['und'][0]['value2'], 'long');
    
    if (!empty($node->body['und'][0]['value'])) {
      $body = strip_tags($node->body['und'][0]['value']);
    }
    else {
      $body = '';
    };

    if ($admin) {
      $action = l('Edit' , 'node/' . $record->oid . '/edit');
    }
    else {
      $action = '';
    }

    $rows[] = array(
      array('data' => l($start_date, 'node/' . $record->oid)),
      array('data' => $end_date),
      array('data' => $body),
      array('data' => $action),
    );
  };

  $header = array(t('Start'), t('End'), t('Notes'));
  if ($admin) {
    $header[] = t('Action');
  }

  $output = array(
    'openhouse' => array(
      '#theme' => 'table',
      '#header' => $header, 
      '#rows' => $rows,
      '#empty' => t('No open house found'),
    ),
  );

  return $output;


};
