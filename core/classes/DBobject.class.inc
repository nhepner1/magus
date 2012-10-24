<?php

abstract class DBobject {

	private $table;
	private $fields = array();
	private $table_info = array();
	private $db;
	
	abstract protected function validate($op = '');
	
	protected function __construct($table) {
		//get existing database connection object
		$this->db = dbconnect::getInstance();
		
		$this->table = addslashes($table);
		$this->setFields();
	}
	
	function __call($method, $args) {

		//check for set_ or get_ calls to the object
		if ( preg_match( "/set(.*)/", $method, $found ) ) {
			if(array_key_exists(strtolower($found[1]), $this->fields)) {
				$this->fields[strtolower($found[1])] = $args[0];
				return true;
			}
		
		} else if(preg_match("/get(.*)/", $method, $found)) {
			if(array_key_exists(strtolower($found[1]), $this->fields)) {
				return $this->fields[strtolower($found[1])];
			}
		}
		
		return false;
	}
	
	private function setFields() {	
		$this->db->executeQuery("SHOW FIELDS FROM $this->table");
		
		foreach($this->db->fetchArray() as $row) {
			$this->table_info[$row['Field']] = $row; 
			$this->fields[$row['Field']] = null;
		}
	}
	
	private function _validate($op) {		
		$validation = $this->validate($op);

		if(isset($validation) && is_array($validation)) {
			foreach($validation['required'] as $required_field) {
				$getField = "get".ucfirst($required_field);
				if(!$this->$getField()) {
					trigger_error("Error creating database entry: <em>$required_field</em> is a required field");
					return false;
				}
			}
		}
		return true;
	}
	
	function load($id = 0) {
		
		if(!is_numeric($id)) {
			
			trigger_error('Invalid user loaded. Use numeric key to retrieve user', E_USER_WARNING);
			return false;
		}
		
		$this->db->executeQuery("SELECT * FROM $this->table WHERE id = $id LIMIT 1");
		$row = $this->db->fetchArrayRow();
		
		if($row) {
			foreach($row as $key => $value) {
				$this->fields[$key] = $value;
			}
		}
	}
	
	function create() {
		
		if($this->_validate('create')){
			
			$data = array();
			foreach($this->fields as $field => $value) {
				//get primary key field for omission
				if(!$this->table_info[$field]['Key'] == 'PRI') {
					$data[$field] = $value;
				} 
	
			}
			
			if($this->db->insert($this->table, $data)){
				return $this->db->insert_id;
			} 
		}
		
		return false;
	}
	

}
/*class DBObject {
	private $id = 0;
	private $table;
	private $fields = array();

	function __construct($table) {
		$this->table = $table;
		$this->fields = $this->getFields();
	}
	
	function __call($method, $args) {
		//check for set_ or get_ calls to the object
		if ( preg_match( "/set_(.*)/", $method, $found ) ) {
			if(array_key_exists($found[1], $this->fields)) {
				$this->fields[$found[1]] = $args[0];
				return true;
			}
		
		} else if(preg_match("/get_(.*)/", $method, $found)) {
			if(array_key_exists($found[1], $this->fields)) {
				return $this->fields[$found[1]];
			}
		}
		return false;
	}
	
	function load($id) {
		global $DB;
		if(!is_numeric($id)) {

			//XXX: Set warning
			return false;
		}
		
		$DB->setLimit(1);
		$result = $DB->query("SELECT * FROM $this->table WHERE id = $id");
		
		if(PEAR::isError($result)) {
			echo $result->getMessage();
			return false;
		}
		
		$row = $result->fetchRow();
		//print_r($row);
		foreach(array_keys($row) as $key) {
			$this->fields[$key] = $row[$key];
		}
	}
	
	function create() {
		global $DB;
		
		//start building the query
		unset($this->fields['id']);
		$fields = implode(", ", array_keys($this->fields));

		//set up query string with variable insert value anchors
		foreach(array_keys($this->fields) as $field) {
			$insert_anchors[] = "?";
		}
		$insert_anchors_str = join(", ", $insert_anchors);
		$sql = "INSERT INTO $this->table ($fields) VALUES ($insert_anchors_str)";
		
		//Assign values to the insert anchors and run the query
		$values = array();
		foreach(array_keys($this->fields) as $field) {
			$values[] = $this->fields[$field];
		}
		
		$sql_h = $DB->prepare($sql);
		if(PEAR::isError($sql_h)) {
			return $sql_h->getMessage();
		}
		
		$result = $sql_h->execute($values);
		if(PEAR::isError($result)) {
			return $result->getMessage();
		}
		return $DB->lastInsertId($this->table, 'id');
	}
	
	function save(){
		global $DB;
		
		//Build update query
		$sets = array();
		$values = array();
		foreach(array_keys($this->fields) as $field) {
			$sets[] = "$field = ?";
			$values[] = $this->fields[$field];
		}
		$set = implode(", ", $sets);
		$values[] = $this->id; //set this as the last value
		
		$sql = "UPDATE $this->table SET $set WHERE id = ?";
		$sql_h = $DB->prepare($sql);
		$DB->execute($sql_h, $values);
	}
	
	function delete() {
		global $DB;
		
		$sql_h = $DB->prepare("DELETE FROM $this->table WHERE id = ?");
		$DB->execute($sql_h, array($this->id));
	}
	
	function getTable() {
		return $this->table;
	}
	
	function getFields() {
		global $DB;
		
		$fields = array();
		
		$result = $DB->query("SHOW FIELDS FROM $this->table");
		while($row = $result->fetchRow()) {
				$fields[$row['field']] = NULL;
		}
		
		return $fields;
	}
}*/