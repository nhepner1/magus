<?php

/**
 * Class for multiple and general query results.
 */
 
// TODO: see where addslashes() and htmlspecialchars() are needed. 
class DBQuery {
  
  /**
   * Contains the database connection object
   */
  private $DBconnect;

  /**
   * Contains the last query run
   */ 
  private $last;
  
  /**
   * Constructor
   */
  public function __construct($DBconnect) {
    $this->setDBconnect($DBconnect);
  }
  
  /**
   * $DBconnect set accessor
   * 
   * @return This DBQuery object
   */
  private function setDBConnect($DBconnect) {
    $this->DBconnect = $DBconnect;
    
    return $this;
  }
  
  /**
   * $DBconnect get accessor
   * 
   * @return DBconnect the database connection object
   */
   private function getDBConnect() {
     return $this->DBconnect;
   }
   
   /**
    * $last set accessor
    */
    private function setLast($last) {
      $this->last = $last;
    }
    
    /**
     * $last get accessor
     */
    public function getQuery() {
      return $this->last;
    }
    
  /**
   * Sanitize and run a query string.
   * 
   * @param $queryStr
   *  Query string to be run.
   */
  public function executeQuery($queryStr) {
    
    // Be cool, wrap your tool...
    $queryStr = $this->getDBConnect()->real_escape_string($queryStr);

    if(!$result = $this->getDBConnect()->query($queryStr)) {
      trigger_error('Error executing query: '.$this->getDBConnect()->error, E_USER_ERROR);
    } else {
      $this->last = $result;
    }
    
    return $result;
  }
  
  /**
   * Delete records from the database
   * 
   * @param $table
   *  String the table to remove rows from
   * @param $condition
   *  String condition for which rows are to be removed
   * @param int $limit 
   *  The number of rows to be removed
   * @return Current DBQuery instance
   */
  public function delete($table, $condition, $limit) {
    $limit = ($limit == '') ? '': ' LIMIT '.$limit;
    
    //TODO: convert to vsprintf()
    $delete = "DELETE FROM {$table} WHERE {$condition} {$limit}";
    $this->executeQuery($delete);
    
    return $this;
  }
  
  /**
   * Update records in the database
   * 
   * @param $table
   *  Table to run the query against
   * @param $changes
   *  Array of field => value pairs to set
   * @param $condition
   *  condition for setting the update where statement
   * @return bool
   */
  public function update($table, $changes, $condition) {
    
    //TODO: Convert to vsprintf and set to use $this->_stringQuotes() or similar
    $update = "UPDATE ".$table." SET ";
    foreach($changes as $field => $value) {
      $update .= "`".$field."`='{$value}',";
    }
    
    // remove training comma
    $update = substr($update, 0, -1);
    if($condition != '') {
      $update .= " WHERE ".$condition;
    }
    
    return $this->executeQuery($update);
  }
  
  /**
   * Insert records into the database
   * 
   * @param $table
   *  Table to run the query against
   * @param $data
   *  Data to insert as a field => value pair
   * @return 
   */
  public function insert($table, $data) {
    $query_vars = array();
    if(!is_array($data) || empty($data)) {
      return false;
    }
    
    array_walk($data, array($this, '_stringQuotes'));
    
    $query_vars = array(
      'table' => $table,
      'fields' => implode("`, `", array_keys($data)),
      'values' => implode(', ', $data)
    );
  
    $format = "INSERT INTO `%s` (`%s`) VALUES (%s)";
    $insert = vsprintf($format, $query_vars);
    return $this->executeQuery($insert);
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
  
  private function _stringQuotes(&$value, $key) {
    $value = is_numeric($value) ? $value : "'".$value."'";
  }
}


