<?php

spl_autoload_register('magus_autoload_classes');

set_exception_handler('magus_exception');

function getDSN() {
	$registry = Registry::instance();
	
	return 	htmlentities($registry->setting('db_type'))."://".
			htmlentities($registry->setting('db_user').":".
			htmlentities($registry->setting('db_pass'))."@".
			htmlentities($registry->setting('db_host')."/".
			htmlentities($registry->setting('db_name'))));
}

function magus_autoload_classes($class_name) {
	$paths = array(CLASSES_PATH, PLUGINS_PATH.DS.$class_name);
	
	foreach($paths as $path) {
		if(file_exists($path.DS."$class_name.class.inc")) { if((require_once $path.DS."$class_name.class.inc") !== false) { return; } }
		else if(file_exists($path.DS."$class_name.plugin.php")) { if((require_once $path.DS."$class_name.plugin.php") !== false) { return; } }
	}
}

function magus_exception($exception) {
	
}

function pre($content) {
	print "<pre>".print_r($content, true)."</pre>";
}