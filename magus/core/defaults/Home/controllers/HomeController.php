<?php namespace Magus\Core\Defaults\Home\Controller;

use \Magus\Core\Theme\Controller;

class HomeController extends Controller {
  public function buildResponse() {
    parent::buildResponse();
    $this->getPage()->setRegion('header', "Home Controller");
    $this->getPage()->setRegion('content', "Welcome to Magus");
  }
}