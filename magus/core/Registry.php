<?php namespace Magus\Core;

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

  /**
   * This allows us to call the settings array dynamically
   * based on an arbitrary number of nested array keys.
   *
   * @return string
   */
  public function getSetting() {
    $setting = '';
    $args = func_get_args();
    $keys = array();

    foreach($args as $key) {
      $keys[] = str_replace("'", "\\'", $key);
    }


    $index = "['". join("']['", $keys) . "']";

    eval("\$setting = self::\$settings{$index};");

    return $setting;
  }

  public function loadConfigFile($filename) {

    if(file_exists($filename)) {
      $config = yaml_parse_file($filename);

      foreach ($config as $key => $settings) {
        $this->setting($key, $settings);
      }
    }
  }
}