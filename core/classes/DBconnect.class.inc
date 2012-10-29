<?php

class DBconnect {
  private static $factory;
  
  /**
   * Container for multiple database connection resources.
   */
  private $connections = array();
  
  /**
   * Pointer for the current active database connection.
   */
  private $activeConnection = 0;
    
  /**
   * Prevent cloning of the object: issues an E_USER_ERROR if this is attempted
   * 
   * @return void
   */
  public function __clone() {
    trigger_error('Cloning the registry is not permitted', E_USER_ERROR);
  }
    
  public static function getFactory()
  {
      if (!self::$factory)
          self::$factory = new DBconnect();
      return self::$factory;
  }

  public function addConnection($id, $db_host, $db_user, $db_pass, $db_name) {
    $this->dbs[$id] = mysqli($db_host, $db_user, $db_pass, $db_name);
    
    return $this;
  }
  
  public function connection() {
      if (!$db)
          $db = new mysqli();
      return $db;
  }
  
  /**
   * Change which database connection is actively used for the next operation
   * 
   * @param int new connection id
   * @return Current DBConnect instance
   */
  public function setActiveConnection(int $new) {
    $this->activeConnection = $new;
    
    return $this;
  }
}

/**
 * Class for establishing, managing, and distributing database connection resources.
 */
class DBconnect {

	/**
	 * Container for multiple database connection resources.
	 */
	private static $connections = array();
  
  /**
   * Pointer for the current active database connection.
   */
	private $activeConnection = 0;
	
  /**
   * Stores singleton instance of DBconnect object.
   */
	private static $instance; 
	
	/**
	 * Constructor
	 */
	private function __construct() {}
	
	/**
	 * Prevent cloning of the object: issues an E_USER_ERROR if this is attempted
   * 
   * @return void
	 */
	public function __clone() {
		trigger_error('Cloning the registry is not permitted', E_USER_ERROR);
	}
	
	/**
   * Singleton object instance control
   * 
   * @return the active DBConnect instance
   */
	public static function getInstance(){
		if(!isset(self::$instance)) {
			$obj = __CLASS__;
			self::$instance = new $obj();
		}
		
		return self::$instance;
	}
	
  /**
   * Create a database connection
   * 
   * @param $host
   *  Hostname of the requested database.
   * @param $user
   *  Username of the requested database.
   * @param $password
   *  Password associated with the Username for the requested database
   * @param $database
   *  Name of the database to use for connection.
   * @return The activeConnection id for the newly created database.
   */
	public function connect($host, $user, $password, $database) {
	  
    //@TODO: Create abstraction layer to use multiple database types.
    //@TODO: Add a string based assignment for $connections ids
		self::$connections[] = new mysqli($host, $user, $password, $database);
    
		$connection_id = count(self::$connections) -1;

		if(mysqli_connect_errno()) {
			trigger_error('Error connecting to host. '.self::$connections[$connection_id]->error, E_USER_ERROR);
		}
		
		return $connection_id;
	}

	/**
	 * Close active connection
   * 
	 * @return Current DBConnect instance
	 */
	public function closeConnection() {
		$this->connections[$this->activeConnection]->close();
    
    return $this;
	}
	
	/**
	 * Change which database connection is actively used for the next operation
   * 
	 * @param int new connection id
	 * @return Current DBConnect instance
	 */
	public function setActiveConnection(int $new) {
		$this->activeConnection = $new;
    
    return $this;
	}
	
	/**
	 * Deconstruct the object
	 * close all of the database connections
	 */
	public function __deconstruct(){
		foreach($this->connections as $connection) {
			$connection->close();
		}
	}
}
