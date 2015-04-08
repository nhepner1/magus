<?php namespace Magus\Core;

class Plugin {
  protected $name;
  protected $weight = 0;
  protected $enabled = 0;
  protected $path;

  public function __construct($name) {
    $this->setName($name);
  }

  public function setName($name) {
    $this->name = $name;
  }

  public function getName() {
    return $this->name;
  }

  public function setWeight($weight) {
    $this->weight = $weight;
  }

  public function getWeight() {
    return $this->weight;
  }

  public function enable() {
    $this->enabled = TRUE;
  }

  public function setPath($path) {
    $this->path = $path;
  }

  public function getPath() {
    return $this->path;
  }

  public function isEnabled() {
    if($this->enabled) {
      return TRUE;
    }

    return FALSE;
  }
}