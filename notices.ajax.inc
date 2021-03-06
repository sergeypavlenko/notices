<?php

function notices_remove_ajax($noticeid,$count){
  global $user;

  $notice=noticeid_load($noticeid);
  if($user->uid == $notice->uid){
    notices_delete($noticeid);
  }else{
    $admin_uid=variable_get('pg_account_admin_uid','1');
    if(!empty($admin_uid)){
      //notify admin about balance update
      $noticeadmin->uid=$admin_uid;
      $noticeadmin->teaser = t('Hack attempt from !uid (!IP) to !noticeid',array('!uid' => $user->uid, '!noticeid' => $noticeid,'!IP' => $user->hostname));
      $noticeadmin->body = t('Hack attempt from !uid (!IP) to !noticeid',array('!uid' => $user->uid, '!noticeid' => $noticeid,'!IP' => $user->hostname));
      $noticeadmin->callback = 'notice';
      notices_save($noticeadmin);
    }
    print drupal_to_js(array('status' => TRUE, 'data' => t('You are trying to hack our system. We sent notification about this action to system administrator.')));  
    exit();  
  }
  $output = '';
  
  if($notice = db_fetch_object(db_query('SELECT * FROM {notices} WHERE uid=%d ORDER BY new DESC,timestamp DESC LIMIT %d OFFSET %d',$user->uid, 1,$count))){
    $output .= '<div id="notices">';
    $output .= theme('notices_view_teaser', $notice);
    $output .= "</div>";
  }

  print drupal_to_js(array('status' => TRUE, 'data' => $output));
  exit();
}

function notices_mark_read_ajax($noticeid = NULL){
  global $user;
  if($noticeid == 'all'){
    db_query("UPDATE {notices} set new=0 WHERE uid = :uid", array( ':uid' => $user->uid));
  }else{
    db_query("UPDATE {notices} set new=0 WHERE noticeid = :noticeid AND uid = :uid", array(':noticeid' => $noticeid, ':uid' => $user->uid));
  }
  return;
  
}

function notices_load_ajax(){
  global $user;
  $output = '';
  
  $notice = db_fetch_object(db_query('SELECT * FROM {notices} WHERE uid=%d ORDER BY new DESC,timestamp DESC LIMIT %d OFFSET %d',$user->uid, 1,2));
  
  $output .= '<div id="notices">';
  $output .= theme('notices_view_teaser', $notice);
  $output .= "</div>";

  print drupal_to_js(array('status' => TRUE, 'data' => $output));
  exit();
  
}