<?php

/**
 * @TODO: Build out event chain class as event
 */

// Instantiate the autoloader so that we can load all of our subsequent classes.
$loader = new \Magus\Core\AutoLoader();
$loader->register();
$loader->addNameSpace('Magus\Core', CORE_PATH);

// Instantiate the registry and import some basic initial settings.
$registry = \Magus\Core\Registry::getInstance();
$registry->loadConfigFile(DEFAULTS_PATH . DS . "settings.yml");
$registry->loadConfigFile(BASE_PATH
  . DS
  . $registry->getSetting('application', 'path')
  . DS
  . 'settings'
  . DS
  . 'settings.yml');


// Import the remaining namespace path definitions into the loader.
foreach($registry->getSetting('namespaces') as $namespace => $path) {
  $loader->addNameSpace($namespace, $path);
}

// Initialize session and provide arguments.
$session = new \Magus\Core\Session();
$session->setSessionName($registry->getSetting('sessions', 'session_name'))
  ->setSecureConnectionsOnly($registry->getSetting('sessions', 'secure_connections_only'))
  ->startSession();

$registry->setting('session', $session);

$dbconnect = \Magus\Core\Database\DBconnect::getInstance();
$dbconnect->connect('main',
  $registry->getSetting('database', 'db_host'),
  $registry->getSetting('database', 'db_user'),
  $registry->getSetting('database', 'db_pass'),
  $registry->getSetting('database', 'db_name'),
  TRUE
);

// Register request. @TODO: Set separate handlers for GET and POST requests
$request = new Magus\Core\Request($_SERVER, $_GET, $_POST);
$registry->setting('request', $request);

// Set up a router so that we can register routes.
$router = new Magus\Core\Router($pluginManager);

// Load all plugins.
$pluginManager = new Magus\Core\PluginManager();
$pluginManager->addPluginDirectory(PLUGINS_PATH);

$plugins = $registry->getSetting('plugins');
foreach($plugins as $plugin_name => $plugin_config) {

  // Determine Plugin Path
  $plugin_path = isset($plugin_config['path']) ? $plugin_config['path'] : PLUGINS_PATH.DS.$plugin_name;

  $plugin = new Magus\Core\Plugin($plugin_name);
  $plugin->setPath($plugin_path);

  // Determine plugin prefix
  $plugin_namespace_prefix = isset($plugin_config['namespace_prefix']) ? $plugin_config['namespace_prefix'] . '\\' : 'Magus\Plugins\\';

  if($plugin_config['enabled']) {
    $plugin->enable();

    // Register plugin namespaces with Autoloader;
    $controller_namespace = $plugin_namespace_prefix . $plugin->getName() . "\\Controller";

    $loader->addNameSpace($controller_namespace, $plugin->getPath() . DS . "controllers");

    $models_namespace = $plugin_namespace_prefix . $plugin->getName() . "\\Models";
    $loader->addNameSpace($models_namespace, $plugin->getPath() . DS . "models");

    $views_namespace = $plugin_namespace_prefix . $plugin->getName() . "\\Views";
    $loader->addNameSpace($views_namespace, $plugin->getPath() . DS . "views");

    $routes_file = $plugin->getPath() . DS . 'routes.yml';

    if(file_exists($routes_file)) {
      // Add any new routes created by plugins.
      $router->loadRoutesFromConfig($routes_file);
    }
  }
  $pluginManager->addPlugin($plugin);
}

$response_handler = $router->getControllerHandler('pages', $request->getUri());

$page = new Magus\Core\Theme\Page();
$response = new $response_handler['controller']($page);

print $response->render();

/*----------------------*/

/*
if($session->isValidSession()) {
    $content = "You are logged in!";
} else {
    $block = new Block();
    $block->setTemplate(THEMES_PATH."/default/login.tpl.php");
    $content = $block->render();
}

/**/


