<?php 

session_start();

define('DS', DIRECTORY_SEPARATOR);

define('BASE_PATH', dirname(__FILE__));
define('CORE_PATH', BASE_PATH.DS."core");
define('INCLUDES_PATH', CORE_PATH.DS."includes");
define('PLUGINS_PATH', BASE_PATH.DS."plugins");
define('CLASSES_PATH', CORE_PATH.DS."classes");
define('THEMES_PATH', BASE_PATH.DS."themes");

require_once INCLUDES_PATH.DS."functions.php";
require_once INCLUDES_PATH.DS."config.php";

$registry = Registry::getInstance();

$page = new Page();
$page->setTitle('Magus v2.0: Electric Boogaloo');
$page->setTheme('default'); //Leave in for dependency injection. Get the theme 
								//var from registry when it's available
$page->setRegion('header', "Magus v2.0: Electric Boogaloo");
$page->setRegion('left_sidebar', "Tada!!!");
$page->setRegion('right_sidebar', "Wicked");
$page->setRegion('footer', "BAM!! Footer");

$dbconnect = DBConnect::getInstance();
$dbconnect->connect('main', $registry->setting('db_host'), $registry->setting('db_user'), $registry->setting('db_pass'), $registry->setting('db_name'), TRUE);


$dbusers = new DBusers(new DBQuery($dbconnect->connection()));
$dbusers->setUsername('admin');
$dbusers->setPassword('testpass');
$dbusers->setEmail('nick@hepnermedia.com');

$dbusers->create();

$page->setRegion('content', '<pre>'.print_r($dbusers, TRUE).'</pre>');
print $page->render();

