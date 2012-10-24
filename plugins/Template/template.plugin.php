<?php

class Template {
	private $path;
	private $template; 
	
	function __construct() {

	}
	
	function build() {
		ob_start();
		include $this->getPath().DS.$this->getTemplate().".html";
		return ob_get_clean();		
	}
	
	public function setPath($path) { $this->path = $path; }
	public function getPath() { return $this->path; }
	
	public function setTemplate($template) { $this->template = $template; }
	public function getTemplate() { return $this->template; }

}