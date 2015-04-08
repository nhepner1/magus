<?php

class Router{

  protected $class_convention = '';
  protected $files_convention = '';
  protected $routes = array();
  protected $plugin_manager;
  protected $routes_config_filename = "routes.yml";
  protected $paths = array();

  public function __construct($plugin_manager) {
    $this->setPluginManager($plugin_manager);
    $this->loadRoutes();
  }

  /**
   * @return mixed
   */
  public function getPluginManager()
  {
    return $this->plugin_manager;
  }

  /**
   * @param mixed $plugin_manager
   */
  public function setPluginManager(PluginManager $plugin_manager)
  {
    $this->plugin_manager = $plugin_manager;
  }

  /**
   * @return mixed
   */
  public function getDefaultPath()
  {
    return $this->default_path;
  }

  /**
   * @param mixed $default_path
   */
  public function setDefaultPath($default_path)
  {
    $this->default_path = $default_path;
  }

  /**
   * @return string
   */
  public function getRoutesConfigFilename()
  {
    return $this->routes_config_filename;
  }

  /**
   * @param string $routes_config_filename
   */
  public function setRoutesConfigFilename($routes_config_filename)
  {
    $this->routes_config_filename = $routes_config_filename;
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

    if(!$uri_request) {
      $controller_info = array(
        'controller' => "DefaultControllerHandler",
        'controller_path' => '',
      );

      return $controller_info;
    }

    // @TODO: Needs more distinct error handling.
    if(!isset($this->routes[$request_type][$uri_request]['controller'])
      || !file_exists($this->routes[$request_type][$uri_request]['controller_path'])) {

      return "Default404Controller";
    }

    require_once($this->routes[$request_type][$uri_request]['controller_path']); // Need to sanitize.

    return $this->routes[$request_type][$uri_request];
  }
}


