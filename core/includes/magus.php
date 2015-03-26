<?php

$registry = Registry::getInstance();
$registry->loadConfigFile(CONFIG_PATH.DS."config.yml");

// Initialize session and provide arguments.
$session = new Session();
$session->setSessionName($registry->getSetting('sessions', 'session_name'))
  ->setSecureConnectionsOnly($registry->getSetting('sessions', 'secure_connections_only'))
  ->startSession();

$registry->setting('session', $session);

$dbconnect = DBconnect::getInstance();
$dbconnect->connect('main',
  $registry->getSetting('database', 'db_host'),
  $registry->getSetting('database', 'db_user'),
  $registry->getSetting('database', 'db_pass'),
  $registry->getSetting('database', 'db_name'),
  TRUE
);

// Initiate form handling
if($_POST) {

    //TODO: Create observer for registered forms to identify and process post requests
    if($_POST['username'] && $_POST['password']) {

        $auth = new Authentication(new DBQuery($dbconnect), $_POST['username'], $_POST['password']);

        $userauth = $auth->authenticateUser();
        if($userauth){
          $user = new User(new DBQuery($dbconnect));
          $user->load($userauth['id']);
          $_SESSION['user'] = $user;
        }
    }
}

$request = new Request($_SERVER, $_GET, $_POST);
$registry->setting('request', $request);

// Load all plugins.
$pluginManager = new PluginManager();
$pluginManager->addPluginDirectory(PLUGINS_PATH);

$plugins = $registry->getSetting('plugins');
foreach($plugins as $plugin_name => $plugin_config) {

  $plugin = new Plugin($plugin_name);
  $plugin->setPath(PLUGINS_PATH.DS.$plugin_name);

  if($plugin_config['enabled']) {
    $plugin->enable();
  }
  $pluginManager->addPlugin($plugin);
}

// Set up Default response.
$page = new Page();
$page->setTitle('Magus v2.0: Electric Boogaloo');
$page->setTheme($registry->getSetting('application', 'theme') ? $registry->getSetting('application', 'theme') : 'default');
$page->setRegion('header', "Magus v2.0: Electric Boogaloo");
$page->setRegion('left_sidebar', "Tada!!!");
$page->setRegion('right_sidebar', "Wicked");
$page->setRegion('footer', "<a href='logout'>Logout</a>");
$page->setRegion('content', "Default Template");

$router = new Router($pluginManager);
$route_handler_info = $router->getControllerHandler('pages', 'logout');

require_once $route_handler_info['controller_path']; // @TODO: Needs to go into autoloader.

$response = new $route_handler_info['controller']($page, $session);
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


