<?php

abstract class DBobject {

	private $table;
	private $fields = array();
	private $table_info = array();
	private $dbquery;
  private $primary_key;
	private $db;
	
	abstract protected function validate($op = '');
	
	protected function __construct(DBQuery $dbquery, $table) {
		//get existing database connection object
		$this->_setDBquery($dbquery);
		
		$this->table = addslashes($table);
		$this->setFields();
    $this->detectPrimaryKey();
	}
	
	function __call($method, $args) {

		//check for set_ or get_ calls to the object
		if ( preg_match( "/set(.*)/", $method, $found ) ) {
			if(array_key_exists(strtolower($found[1]), $this->fields)) {
				$this->fields[strtolower($found[1])] = $args[0];
				return true;
			}
		}
		
		return false;
	}
	
	private function setFields() {	
		$this->_getDBquery()->executeQuery("SHOW FIELDS FROM $this->table");
		
		foreach($this->_getDBquery()->fetchArray() as $row) {
			$this->table_info[$row['Field']] = $row; 
			$this->fields[$row['Field']] = null;
		}
	}
  
  public function getField($fieldname) {
    return $this->fields[$fieldname];
  }
  
  private function getFields() {
    return $this->fields;
  }
  
  /**
   * Search through existing table information retrieved from
   * the database and determine which field is the primary key
   * if one is set.
   * 
   * @return This DBobject instance
   */
  private function detectPrimaryKey() {
    if(!empty($this->table_info)) {
      foreach($this->table_info as $field_name => $table_info) {
        if($table_info['Key'] == 'PRI') {
          $this->primary_key = $field_name;
          return $this;
        }
      }
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
	
	public function load($id = 0) {
		
		if(!is_numeric($id)) {
			
			trigger_error('Invalid user loaded. Use numeric key to retrieve user', E_USER_WARNING);
			return false;
		}
		
		$this->_getDBquery()->executeQuery("SELECT * FROM $this->table WHERE id = $id LIMIT 1");
		$row = $this->_getDBquery()->fetchArrayRow();
		
		if($row) {
			foreach($row as $key => $value) {
				$this->fields[$key] = $value;
			}
		}
	}
	
	public function create() {
		
		if($this->_validate('create')){
			
			$data = array();
			foreach($this->fields as $field => $value) {
				//get primary key field for omission
				if(!$this->table_info[$field]['Key'] == 'PRI') {
					$data[$field] = $value;
				} 
	
			}
			
			if($this->_getDBquery()->insert($this->table, $data)){
				return $this->_getDBquery()->insert_id();
			} 
		}
		
		return false;
	}
  
  public function save() {
    $fields = $this->getFields();
    if(!$fields[$this->primary_key]) {
      return $this->create();
    }
    if($this->_validate('save')) {
      $condition = sprintf("`%s` = %d", $this->primary_key, $fields[$this->primary_key]);
      unset($fields[$this->primary_key]);
      $this->_getDBquery()->update($this->table, $fields, $condition);
    }
  }
  
  public function delete() {
    if($this->getField($this->primary_key)) {
      $condition = 'id = '.intval($this->getField($this->primary_key));
      $this->_getDBquery()->delete($this->table, $condition, 1);
    }
  }
  
  protected function _getDBquery() {
    return $this->dbquery;
  }
  
  protected function _setDBquery(DBQuery $dbquery) {
    $this->dbquery = $dbquery;
  }
}