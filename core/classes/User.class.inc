<?php

class User extends DBobject {
	function __construct(DBQuery $dbquery) {
		parent::__construct($dbquery, 'users');
	}
	
	protected function validate($op = '') {
		switch($op) {
			case 'create':
				return array(
					'required'	=>	 array('username', 'password', 'email')
				);
			case 'save':
			
		}
	}
}