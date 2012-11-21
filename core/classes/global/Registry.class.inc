<?php 

class Registry {
	
	/**
	 * Do I want this thing to handle objects? I don't think I do. 
	 * I'll leave the code here for now, but I *think* that I'm going to
	 * want objects on their own for cleaner syntax.
	 */ 
	
	private static $settings = array();
	private static $instance;
	
	/**
	 * Private constructor to prevent it object being created directly
	 * @access private
	 */
	private function __construct() {}
	
	/**
	 * Prevent cloning of the object: throw exception
	 */
	public function __clone() { throw new Exception('Cloning the registry is not permitted'); }
	
	// Singleton object instance control
	public static function getInstance(){
		if(!isset(self::$instance)) {
			$obj = __CLASS__;
			self::$instance = new $obj;
		}
		
		return self::$instance;
	}
	
	/**
	 * Set configuration setting
	 * @param $key
	 * @param $data
	 * @return unknown_type
	 */
	public function setting($key, $data = NULL) {
		if($data !== NULL) {
			self::$settings[$key] = $data;
		} else {
			return self::$settings[$key];
		}		
	}
}