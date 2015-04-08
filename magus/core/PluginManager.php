<?php namespace Magus\Core;

class PluginManager {
  protected $plugin_directories = array();
  protected $plugin_configuration_files = array();
  protected $plugins = array();

  public function __construct() {

  }

  public function addPluginDirectory($path) {
    //@TODO: Validate directory existence
    $this->plugin_directories[] = $path;

    return $this;
  }

  public function getPluginDirectories() {
    return $this->plugin_directories;
  }

  public function addPlugin(Plugin $plugin) {
    $this->plugins[] = $plugin;
  }

  public function getPlugins() {
    return $this->plugins;
  }

  public function addPluginConfigFile($path) {
    //@TODO: Do proper file check
    $this->plugin_configuration_files[] = $path;

    return $this;
  }

  public function getEnabledPlugins() {
    $plugins = array();

    foreach($this->plugins as $plugin) {
      if($plugin->isEnabled()) {
        $plugins[] = $plugin;
      }
    }

    return $plugins;
  }
}