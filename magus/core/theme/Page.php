<?php namespace Magus\Core\Theme;

class Page {
	
	private $theme;
	private $css = array();
	private $js = array();
	
	private $authorised = TRUE;
	
	private $title = '';
	
	private $regions = array();
	
	function __construct() {
		$this->setTheme('default');
	}
	
	/* --- ACCESSORS --- */
	public function getTitle() {
		return $this->title;
	}
	
	public function setTitle($title) {
		$this->title = $title;
	}
	
	/*public function addRegion($region) {
		if($region instanceof Region) {
			$this->regions[$region->getRegionName()] = $this->region;
			return TRUE;
		}
		
		return FALSE;
	}*/
	
	public function setRegion($key, $content) {
		$this->regions[$key] = $content;
	}
	
	public function addCss($css_filename) {
		$this->css[] = $css_filename;
	}
	
	public function addJs($js_filename) {
		$this->js[] = $js_filename;
	}
	
	public function setTheme($theme) {
		$this->theme = ($theme) ? $theme : 'default';  
	}
	
	public function getTheme() {
		return $this->theme; 
	}
	
	/* --- end ACCESSORS --- */
	/* --- PRIVATE FUNCTIONS --- */
	private function buildCSS() {
		foreach($this->css as $css_file) {
			
		}
	}
	
	private function buildJS() {
		foreach($this->js as $js_file) {
			
		}
	}
	
	/* --- end PRIVATE FUNCTIONS --- */
	/* --- PUBLIC FUNCTIONS --- */
	public function render() {
		$title = $this->getTitle();
		$theme = $this->getTheme();
		$css = $this->buildCss();
		
		extract($this->regions);

		ob_start();
		include MAGUS_PATH . DS . "themes/".$this->theme."/main.tpl.php"; //TODO: Template should be dynamically set.
		return ob_get_clean();
	}
	
	/* --- end PUBLIC FUNCTIONS --- */
}