<?php

class Router{

  protected $class_convention = '';
  protected $files_convention = '';
  protected $routes = array();
  protected $plugin_manager;
  protected $routes_config_filename = "routes.yml";


  public function __construct($plugin_manager) {
    $this->setPluginManager($plugin_manager);
    $this->loadRoutes();
  }

  public function setPluginManager(PluginManager $plugin_manager) {
    $this->plugin_manager = $plugin_manager;
  }

  public function getPluginManager() {
    return $this->plugin_manager;
  }

  public function setRoutesConfigFilename($routes_config_filename) {
    $this->routes_config_filename = $routes_config_filename;
  }

  public function getRoutesConfigFilename() {
    return $this->routes_config_filename;
  }

  public function addRoute($request_type, $route, $route_info = array()) {
    if(!isset($this->routes[$request_type])) {
      $this->routes[$request_type] = array();
    }

    $this->routes[$request_type][$route] = $route_info;

    return $this;
  }

  protected function loadRoutes() {

    foreach($this->getPluginManager()->getEnabledPlugins() as $plugin) { // Check for dependency injection
      $plugin_routes_path = $plugin->getPath().DS.$this->routes_config_filename;


      if(file_exists($plugin_routes_path)) {

        $routes_config = yaml_parse_file($plugin_routes_path);
        foreach($routes_config as $request_type => $routes) {
          foreach($routes as $route => $route_info) {
            $route_info += array(
              'controller_path' => $plugin->getPath()."/controllers/" . $route_info['controller'] . '.class.inc',
            );

            $routes_config[$request_type][$route] = $route_info;
          }
        }

        $this->routes = array_merge_recursive($this->routes, $routes_config);
      }
    }
  }

  public function getControllerHandler($request_type, $uri_request) {

    // @TODO: Needs more distinct error handling.
    if(!isset($this->routes[$request_type][$uri_request]['controller'])
      || !file_exists($this->routes[$request_type][$uri_request]['controller_path'])) {

      return "404 error"; // @TODO: Return 404 controller
    }

    require_once($this->routes[$request_type][$uri_request]['controller_path']); // Need to sanitize.

    return $this->routes[$request_type][$uri_request];
  }
}


