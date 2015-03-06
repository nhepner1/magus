<?php

class Region {
	
	private $plugins = array();
	
	public function __construct() {}
	

	private function sortBlocks() {
		usort($this->plugins, array($this, "compareBlockWeight"));
	} 
	
	private function compareBlockWeight($a, $b) {
		if($a['weight'] == $b['weight']) {
			return 0;
		}
		
		return ($a['weight'] < $b['weight'])? -1 : 1;
	}
	
	public function addBlock($plugin_name, $instance, $weight = 0 ){
		$this->plugins[] = array(	'plugin' 		=> $plugin_name,
									'instance'		=>	$instance,
									'weight'		=>	$weight);
		

	}	
	
	public function render() {
		$this->sortBlocks();
		
		$return = '<br /><br /><br />';
		foreach($this->plugins as $plugin) {
			$return .= $plugin['instance']->build();
		}
		/*if(!$file) $file = $this->file;
		extract($this->vars);
		ob_start();
		include($file);
		return ob_get_clean();*/
		
		return $return;
	}
}