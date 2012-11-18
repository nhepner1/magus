<?php

class DBusers extends DBobject {
  function __construct($connection) {
    parent::__construct($connection, 'users');
  }
  
  function validate($op = '') {
    return array(
      'required' => array('username', 'password', 'email')
    );
  }
}
