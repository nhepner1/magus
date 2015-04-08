<?php 

define('DS',            DIRECTORY_SEPARATOR);
define('BASE_PATH',     dirname(__FILE__));
define('MAGUS_PATH',    BASE_PATH  . DS . "magus");
define('CORE_PATH',     MAGUS_PATH . DS . "core");
define('INCLUDES_PATH', MAGUS_PATH . DS . "includes");
define('SETTINGS_PATH', MAGUS_PATH . DS . "settings");
define('PLUGINS_PATH',  MAGUS_PATH . DS . "plugins");

require_once CORE_PATH.DS."AutoLoader.php";
require_once INCLUDES_PATH.DS."exceptions.php";
require_once INCLUDES_PATH.DS."debug.php";
require_once INCLUDES_PATH.DS."magus.php";

#TODO: Validate application requirements before bootstrapping.

#TODO: Include database verification and YAML based install wizard if uninitiated



