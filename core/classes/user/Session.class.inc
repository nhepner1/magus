<?php

class Session {
	var $username;
	var $session_id;
	var $roles = array();
	var $time;
	var $logged_in;
	var $userinfo = array();
	var $url;
	var $referrer;
	var $db;	
	
	function __construct() {
		
		$this->time = time();
		$this->startSession();
	}
	
	function startSession() {
		
		
	}
	
	function checkLogin() {
		
	}
	
	function login() {
		
	}
	
	function logout() {
		
	}
}
