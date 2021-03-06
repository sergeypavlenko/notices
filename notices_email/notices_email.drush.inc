<?php
// $Id$

/**
 * @file
 *   Drush support for node_export.
 */

/**
 * Implementation of hook_drush_command().
 */
function notices_email_drush_command() {
  $items = array();

  $items['notices_email'] = array(
    'callback' => 'drush_notices_email_callback',
    'description' => "Invoke notices_email jobs.",
    'arguments' => array(
      'type' => 'no argumet\'s yet.',
    ),
    'examples' => array(
      'drush notices_email' =>
        'Invoke notices_email jobs.',
    ),
  );

  return $items;
}

/**
 * Implementation of hook_drush_help().
 *
 * This function is called whenever a drush user calls
 * 'drush help <name-of-your-command>'
 *
 * @param
 *   A string with the help section (prepend with 'drush:')
 *
 * @return
 *   A string with the help text for your command.
 */
function notices_email_drush_help($section) {
  switch ($section) {
    case 'drush:notices_email':
      return dt("Invoke notices_email jobs.");
  }
}

/**
 * Drush command callback.
 */

function drush_notices_email_callback() {
  $commands = func_get_args();
  global $_domain;  
  drush_print(dt('We will process notices_email spool '));
  if(drush_confirm(dt('You really want to continue?'))) {
    notices_email_spool();
  }
}