<?php namespace Magus\Core;

class Router{
  protected $default_handler;
  protected $error_404_handler;
  protected $error_403_handler;
  protected $routes = array();

  protected $paths = array();

  public function addRoute($request_type, $route, $route_info = array()) {
    if(!isset($this->routes[$request_type])) {
      $this->routes[$request_type] = array();
    }

    $this->routes[$request_type][$route] = $route_info;

    return $this;
  }

  /**
   * @return array
   */
  public function getRoutes()
  {
    return $this->routes;
  }

  public function loadRoutesFromConfig($filename) {

    if(file_exists($filename)) {

      $routes_config = yaml_parse_file($filename);

      foreach($routes_config as $request_type => $routes) {
        foreach($routes as $route => $route_info) {

          $routes_config[$request_type][$route] = $route_info;
        }
      }

      $this->routes = array_merge_recursive($this->routes, $routes_config);
    }
  }

  public function getControllerType($request_type) {
    switch($request_type) {
      case 'GET':
        return 'pages';
        break;
      case 'POST':
        return 'forms';
        break;
      default:
        return $request_type;
    }
  }

  public function getControllerHandler($request_type, $uri_request) {

    foreach($this->routes[$request_type] as $route_name => $route) {

      if($uri_request == $route['path']) {
        return $this->routes[$request_type][$route_name];
      }
    }

    // @TODO: Needs more distinct error handling.
    if(!isset($this->routes[$request_type][$uri_request]['controller'])) {
      return array('controller' => "Default404Controller");
    }

  }

  /**
   * @param mixed $default_handler
   */
  public function setDefaultHandler($default_handler)
  {
    $this->default_handler = $default_handler;
  }

  /**
   * @return mixed
   */
  public function getDefaultHandler()
  {
    return $this->default_handler;
  }
}


