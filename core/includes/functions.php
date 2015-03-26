<?php

spl_autoload_register('magus_autoload_classes');

set_exception_handler('magus_exception');

function getDSN() {
	$registry = Registry::instance();
	
	return 	htmlentities($registry->getSetting('database', 'db_type'))."://".
			htmlentities($registry->getSetting('database', 'db_user').":".
			htmlentities($registry->getSetting('database', 'db_pass'))."@".
			htmlentities($registry->getSetting('database', 'db_host')."/".
			htmlentities($registry->getSetting('database', 'db_name'))));
}

function magus_autoload_classes($class_name) {
	$paths = array(CLASSES_PATH, PLUGINS_PATH.DS.$class_name);
	
	foreach($paths as $path) {
		if(file_exists($path.DS."$class_name.class.inc")) {
      if((require_once $path.DS."$class_name.class.inc") !== false) {
        return;
      }
    }
	}
}

function magus_exception($exception) {
	
}

function pre($content) {
	return "<pre>".print_r($content, true)."</pre>";
}