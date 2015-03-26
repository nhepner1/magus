<?php

abstract class PageController {

  protected $page;

  public function __construct(Page $page) {
    $this->setPage($page);
  }

  /**
   * @param mixed $page
   */
  public function setPage($page)
  {
    $this->page = $page;
  }

  /**
   * @return mixed
   */
  public function getPage()
  {
    return $this->page;
  }


  public function buildResponse() {

  }

  function render() {

    $this->buildResponse();
    return $this->getPage()->render();
  }

}