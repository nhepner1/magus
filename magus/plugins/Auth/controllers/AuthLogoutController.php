<?php namespace Magus\Plugins\Auth\Controller;

use \Magus\Core\Theme\Controller;

class AuthLogoutController extends Controller {
  public function buildResponse() {
    $this->getPage()->setTitle("TESTING LOGOUT AUTH");
    $this->getPage()->setRegion('header',"Testing my plugin manager");
  }
}