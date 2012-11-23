<?php 

session_start();

define('DS', DIRECTORY_SEPARATOR);

define('BASE_PATH', dirname(__FILE__));
define('CORE_PATH', BASE_PATH.DS."core");
define('INCLUDES_PATH', CORE_PATH.DS."includes");
define('PLUGINS_PATH', BASE_PATH.DS."plugins");
define('CLASSES_PATH', CORE_PATH.DS."classes");
define('THEMES_PATH', BASE_PATH.DS."themes");

require_once INCLUDES_PATH.DS."setup.php";
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

$left_sidebar = new Region();

	$template = new Template();
	$template->setPath(THEMES_PATH.DS.$registry->setting('theme').DS."templates");
	$template->setTemplate('danfro');

	$left_sidebar->addPlugin('Template', $template, 8);
	
	$template = new Template();
	$template->setPath(THEMES_PATH.DS.$registry->setting('theme').DS."templates");
	$template->setTemplate('test_subject');
	$left_sidebar->addPlugin('Template', $template, 6);
/*$left_sidebar->addPlugin('test', 0, 'Stuff', array('test', 'nothin'), 'relaxed', 1121);
$left_sidebar->addPlugin('newtest', 50, "other stuff");
$left_sidebar->addPlugin('third_test', 10, "more stuff");
$left_sidebar->addPlugin('forth_test', 5, "forth stuff");*/
$page->setRegion('left_sidebar', $left_sidebar->render());
print $page->render();

