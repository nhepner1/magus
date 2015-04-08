<?php

class Block {
    var $template;
    var $variables = array();

    public function setTemplate($template) {
        $this->template = $template;
    }

    public function setVariable($name, $value) {
        $this->variables[$name] = $value;
    }

    public function render() {

        if(!$this->template) {
            return "";
        }

        extract($this->variables);

        ob_start();
        include $this->template;
        return ob_get_clean();
    }
}