<?php namespace Magus\Core;

class Session {
	var $user;
	var $session_id;
  var $session_name;
  var $secure_sessions_only;
	var $roles = array();
	var $time;
	var $logged_in;
	var $userinfo = array();
	var $url;
	var $referrer;
	var $db;

	function __construct() {
		
		$this->time = time();
    return $this;
	}
	
	function startSession() {

    //TODO: Record the session ID to database and track IPs/user agents

    $secure = isset($this->secure_sessions_only) ? $this->secure_sessions_only : TRUE;
    $httponly = TRUE; // Set this so that Javascript cannot access the session ID.

    // Forces sessions to only use cookies.
    if (ini_set('session.use_only_cookies', 1) === FALSE) {
        die('Could not initiate a safe session');
        exit();
    }

    // Gets current cookies params.
    $cookieParams = session_get_cookie_params();
    session_set_cookie_params($cookieParams["lifetime"],
        $cookieParams["path"],
        $cookieParams["domain"],
        $secure,
        $httponly);


    // Sets the session name to the one set above.
    if($this->session_name) {
        session_name($this->session_name);
    }
    session_start();            // Start the PHP session
    session_regenerate_id(true);    // regenerated the session, delete the old one.

    return $this;
  }

    function setSessionName($session_name) {
      $this->session_name = $session_name;

      return $this;
    }

    function setSecureConnectionsOnly($secure_sessions_only) {
      $this->secure_sessions_only = (bool)$secure_sessions_only;

      return $this;
    }

    function isValidSession() {
        //TODO: Run logic to verify the session, such as IP checking.
        if($_SESSION && $_SESSION['user']) {
            return TRUE;
        }

        return FALSE;
    }

    function destroySession() {

    }

}
