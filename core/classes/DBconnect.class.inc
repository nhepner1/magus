<?php

class DBconnect {
	

	/**
	 * Allows multiple database connections
	 */
	private static $connections = array();

	/**
	 * Tells the DB object which connection to use
	 */
	private $activeConnection = 0;
	
	private static $instance;
	
	/**
	 * Constructor
	 */
	private function __construct() {}
	
	/**
	 * Prevent cloning of the object: issues an E_USER_ERROR if this is attempted
	 */
	public function __clone() {
		trigger_error('Cloning the registry is not permitted', E_USER_ERROR);
	}
	
	// Singleton object instance control
	public function getInstance(){
		if(!isset(self::$instance)) {
			$obj = __CLASS__;
			self::$instance = new $obj();
		}
		
		return self::$instance;
	}
	
	public function connect($host, $user, $password, $database) {
		$this->connections[] = new mysqli($host, $user, $password, $database);
		$connection_id = count($this->connections) -1;
		if(mysqli_connect_errno()) {
			trigger_error('Error connecting to host. '.$this->connections[$connection_id]->error, E_USER_ERROR);
		}
		
		return $connection_id;
	}

	/**
	 * Close active connection
	 * @return void
	 */
	public function closeConnection() {
		$this->connections[$this->activeConnection]->close();
	}
	
	/**
	 * Change which database connection is actively used for the next operation
	 * @param int new connection id
	 * @return void
	 */
	public function setActiveConnection(int $new) {
		$this->activeConnection = $new;
	}
	
	/**
	 * Store a query in the query cache for processing later
	 * @param String the query string
	 * @return the pointer to the query in the cache
	 */
	public function cacheQuery($queryStr) {
		if(!$result = $this->connections[$this->activeConnection]->query($queryStr)) {
			trigger_error('Error executing and caching query: '.$this->connections[$this->activeConnection]->error, E_USER_ERROR);
			return -1;	
		} else {
			$this->queryCache[] = $result;
			return count($this->queryCache)-1;
		}
	}
	
	/**
	 * Get the number of rows from the cache
	 * @param int the query cache pointer
	 * @return int the number of rows
	 */
	public function numRowsFromCache($cache_id) {
		return $this->queryCache[$cache_id]->num_rows;
	}
	
	/**
	 * Get rows from cached query
	 * @param $cache_id
	 * @return unknown_type
	 */
	public function resultsFromCache($cache_id) {
		return $this->queryCache[$cache_id]->fetch_array(MYSQLI_ASSOC);
	}
	
	/**
	 * Store data in cache
	 * @param array data
	 * @return int the pointer to the array in the data cache
	 */
	public function cacheData($data) {
		$this->dataCache[]=$data;
		return count($this->dataCache)-1;
	}
	
	/**
	 * Get data from the data cache
	 * @param int data cache pointer
	 * @return array data
	 */
	public function dataFromCache($cache_id) {
		return $this->dataCache[$cache_id];
	}
	
	/**
	 * Delete records from the database
	 * @param String the table to remove rows from
	 * @param String condition for which rows are to be removed
	 * @param int the number of rows to be removed
	 * @return void
	 */
	public function delete($table, $condition, $limit) {
		$limit = ($limit == '') ? '': ' LIMIT '.$limit;
		$delete = "DELETE FROM {$table} WHERE {$condition} {$limit}";
		$this->executeQuery($delete);
	}
	
	/**
	 * Update records in the database
	 * @param String the table
	 * @param array of changes field => value
	 * @param String the condition
	 * @return bool
	 */
	public function update($table, $changes, $condition) {
		$update = "UPDATE ".$table." SET ";
		foreach($changes as $field => $value) {
			$update .= "`".$field."`='{$value}',";
		}
		
		// remove training comma
		$update = substr($update, 0, -1);
		if($condition != '') {
			$update .= " WHERE ".$condition;
		}
		
		$this->executeQuery($update);
		
		return true;
	}
	
	/**
	 * Insert records into the database
	 * @param String database table
	 * @param array data to insert field => value
	 * @return bool
	 */
	public function insert($table, $data) {
		//scope vars
		$fields = '';
		$values = '';
		foreach($data as $field => $value) {
			$fields .= "`$field`,";
			$values .= (is_numeric($value) && (intval($value) == $v)) ? $v."," : "'$value',";
		}
		
		//remove trailing commas
		$fields = substr($fields, 0, -1);
		$values = substr($values, 0, -1);
		
		$insert = "INSERT INTO $table ({$fields}) VALUES ({$values})";
		$this->executeQuery($insert);
		return true;
	}
	
	public function executeQuery($queryStr) {
		
		// Be cool, wrap your tool...
		$this->connections[$this->activeConnection]->real_escape_string($queryStr);

		if(!$result = $this->connections[$this->activeConnection]->query($queryStr)) {
			trigger_error('Error executing query: '.$this->connections[$this->activeConnection]->error, E_USER_ERROR);
		} else {
			$this->last = $result;
		}
	}
	
	/**
	 * Get rows from the most recently executed query, excluding cached queries
	 * @return array
	 */
	public function fetchArray() {
		while($row = $this->last->fetch_array(MYSQLI_ASSOC)){
			$return[] = $row; 
		}
		return $return;
	}
	
	public function fetchArrayRow($row_number = 0) {
		$return = $this->fetchArray();
		return $return[$row_number];
	}
	
	/**
	 * Gets the number of affected rows from the previous query
	 * @return int the number of affected rows
	 */
	public function affectedRows() {
		return $this->connections[$this->activeConnection]->affectedRows;
	}
	
	public function insert_id() {
		return $this->last->insert_id;
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
