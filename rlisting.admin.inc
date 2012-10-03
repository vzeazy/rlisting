<?php
/**
 * @file 
 *  Admin funcitons
 */

/**
 * Main admin function form
 */
function rlisting_admin_settings() {

  $vocabs = taxonomy_get_tree(1);
  $terms = array();
  foreach($vocabs as $term) {
    $terms[$term->tid] = $term->name;
  };
  $form['rlisting_showcase_term'] = array(
    '#type' => 'select',
    '#title' => t('Showcase Term'),
    '#options' => $terms,
    '#default_value' => variable_get('rlisting_showcase_term', 3),
    '#description' => t('Select the term to filter the front page slideshow by.'),
  );
  $form['rlisting_config_min_price'] = array(
    '#type' => 'textfield',
    '#title' => t('Min Price'),
    '#default_value' => variable_get('rlisting_config_min_price', '50,000'),
    '#description' => t('Used in search forms'),
  );
  $form['rlisting_config_max_price'] = array(
    '#type' => 'textfield',
    '#title' => t('Max Price'),
    '#default_value' => variable_get('rlisting_config_max_price', '10,000,000'),
    '#description' => t('Used in search forms'),
  );


  return system_settings_form($form);

};

/** 
 * Profile installation functions.
 */


/**
 * Returns a list of tables in the active database.
 *
 * Only returns tables whose prefix matches the configured one (or ones, if
 * there are multiple).
 *
 */
function _rlisting_get_tables() {
  global $databases;
  $db_prefix = $databases["default"]["default"]["prefix"];

  $tables = array();

  if (is_array($db_prefix)) {
    // Create a regular expression for table prefix matching.
    $rx = '/^' . implode('|', array_filter($db_prefix)) . '/';
  }
  else if ($db_prefix != '') {
    $rx = '/^' . $db_prefix . '/';
  }

  $tables = db_find_tables('%');

  foreach($tables as $table) {
    if (is_array($db_prefix)) {
      // Check if table name matches a configured prefix.
      if (preg_match($rx, $table, $matches)) {
        $table_prefix = $matches[0];
        $plain_table = substr($table, strlen($table_prefix));
        if ($db_prefix[$plain_table] == $table_prefix || $db_prefix['default'] == $table_prefix) {
          $tables[] = $table;
        }
      }
    }
    else if ($db_prefix != '') {
      if (preg_match($rx, $table)) {
        $tables[] = $table;
      }
    }
    else {
      $tables[] = $table;
    }
  }

  return $tables;
}

