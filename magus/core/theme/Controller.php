<?php namespace Magus\Core\Theme;

abstract class Controller {

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

// Set up Default response.

    $this->getPage()->setTitle('Magus v2.0: Electric Boogaloo');
    $this->getPage()->setRegion('header', "Magus v2.0: Electric Boogaloo");
    $this->getPage()->setRegion('left_sidebar', "Tada!!!");
    $this->getPage()->setRegion('right_sidebar', "Wicked");
    $this->getPage()->setRegion('footer', "<a href='logout'>Logout</a>");
    $this->getPage()->setRegion('content', "Default Template");
  }

  function render() {

    $this->buildResponse();
    return $this->getPage()->render();
  }
}