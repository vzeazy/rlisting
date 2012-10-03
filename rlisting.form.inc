<?php
/**
 * @fil
 * Form callback for utilitly functions.
 */


/**
 * Display form
 *  Returns renderable form to display value of form fields but with all
 * options disabled. 
 */
function rlisting_display_features_form($form, $form_state, $node) {

  $fields = array(
    'rlisting_features' => array(
      'type' => 'checkboxes',
      'weight' => 1,
    ),    
  );

  $label = '';
  foreach ($fields as $field_name => $info) {
    $field_data = field_info_instance('node', $field_name, 'rlisting');
    $field_info = field_info_field($field_name);

    $label = $field_data['label'];
    $allowed_values = list_allowed_values($field_info);
    $items = field_get_items('node', $node, $field_name);
    $value = $values = array();

    switch($info['type']) {
      case 'checkboxes':
        if ($items) {
          foreach($items as $index => $value) {
            $values[$value['value']] = $value['value'];
          };
          asort($allowed_values);
          $form[$field_name] = array(
            '#type' => 'checkboxes',
            '#title' => $label,
            '#options' => $allowed_values,
            '#disabled' => TRUE,
            '#default_value' => $values,
            '#weight' => $info['weight'],
          );
        };  
        break; 
    };
    
  };

  return $form;

};
