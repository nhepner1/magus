<?php

class Authentication {
  private $username;
  private $password;
  private $password_hash_algorithm = 'sha512';
  private $salt;
  private $dbquery;

  function __construct(DBQuery $dbquery, $username, $password) {
    $this->setUsername($username);
    $this->setPassword($password);
    $this->setDBQuery($dbquery);
  }

  function setUsername($username) {
    $this->username = $username;
  }

  function setPassword($password) {
    //$this->password = hash($this->password_hash_algorithm, $password);
    $this->password = $password;
  }

  function setDBQuery($dbquery) {
    $this->dbquery = $dbquery;
  }

  function getDBQuery() {
    return $this->dbquery;
  }

  function setSalt($salt) {
    $this->salt = $salt;
  }

  function getSalt() {
    return $this->salt;
  }

  function setPasswordHashAlgorithm($algorithm) {
    $this->password_hash_algorithm = $algorithm;
    //TODO: Make sure that if the password algorithm changes, backwards compatibility is maintained
  }

  function getPasswordHashAlgorithm() {
    return $this->password_hash_algorithm;
  }

  function authenticateUser() {

    $this->getDBQuery()->executeQuery("SELECT id FROM users WHERE `username` = '$this->username' AND `password` = '$this->password'");

    if($this->getDBQuery()->getLast()) {
      return $this->getDBQuery()->fetchArrayRow();
    }

    return FALSE;
  }
}