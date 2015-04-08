<?php

spl_autoload_register('magus_autoload_classes');

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

function pre($content) {
  return "<pre>".print_r($content, true)."</pre>";
}