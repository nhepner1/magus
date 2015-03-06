<?php

/**
 * Class for establishing, managing, and distributing database connection resources.
 * 
 * TODO: Set observer to set the active database in the DBQuery object. Maintain dependency injection.
 */
class DBconnect {

	/**
	 * Container for multiple database connection resources.
	 */
	private $connections = array();
  
  /**
   * Pointer for the current active database connection.
   */
	private $activeConnection = 0;
	
  /**
   * Stores singleton instance of DBconnect object.
   */
	private static $instance; 
	
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
   * @param $connection_id
   *  The assigned connection string to associate with the new 
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
	public function connect($connection_id, $host, $user, $password, $database, $setActive = FALSE) {
    
    //@TODO: Create abstraction layer to use multiple database types.
    $this->connections[$connection_id] = new mysqli($host, $user, $password, $database);

		if($this->connections[$connection_id]->connect_errno) {
			trigger_error('Error connecting to host. '.$this->connections[$connection_id]->error, E_USER_ERROR);
		}
    
    if($setActive) {
      $this->setActiveConnection($connection_id);
    }
		
		return $this->connections[$connection_id];
	}

  /**
   * Retrieve active connection
   * 
   * @return Active connection. If no connection is set, trigger error.
   */
  public function connection() {
    
    if(!isset($this->connections[$this->activeConnection])) {
      trigger_error('Active connection not available. Set active connection before requesting.', E_USER_ERROR);
    }
    
    return $this->connections[$this->activeConnection];
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
	public function setActiveConnection($connection_id) {

		$this->activeConnection = $connection_id;
    
    return $this;
	}

  /**
   * Query function to run raw sql against the database. NOT SAFE.
   */
  public function query($sql) {

    $result = $this->connection()->query($sql);

    if(!$result) {
      trigger_error("There was an error with your query: " . $this->connection()->errno . ": " . $this->connection()->error, E_USER_ERROR);
    }

    return $result;
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
