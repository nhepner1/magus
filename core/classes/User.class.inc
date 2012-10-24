<?php

class User extends DBobject {
	function __construct() {
		parent::__construct('users');
	}
	
	protected function validate($op = '') {
		switch($op) {
			case 'create':
				return array(
					'required'			=>	 array('username', 'password', 'email')
				);
			case 'save':
			
		}
	}
}