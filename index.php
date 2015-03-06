<?php 

define('DS', DIRECTORY_SEPARATOR);

define('BASE_PATH', dirname(__FILE__));
define('CORE_PATH', BASE_PATH.DS."core");
define('INCLUDES_PATH', CORE_PATH.DS."includes");
define('CONFIG_PATH', BASE_PATH.DS."config");
define('PLUGINS_PATH', BASE_PATH.DS."plugins");
define('CLASSES_PATH', CORE_PATH.DS."classes");
define('THEMES_PATH', BASE_PATH.DS."themes");

require_once INCLUDES_PATH.DS."functions.php";
require_once CONFIG_PATH.DS."config.php";
require_once INCLUDES_PATH.DS."magus.php";

# Include primary application.
$registry = Registry::getInstance();

#TODO: Validate application requirements before bootstrapping.

#TODO: Include database verification and YAML based install wizard if uninitiated



