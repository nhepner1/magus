<?php

class Request {
  protected $parameters = array();

  protected $request_method;
  protected $protocol;
  protected $base_url;
  protected $port;
  protected $uri;

  protected $query_string_raw;
  protected $query_arguments = array();

  protected $request_time;

  protected $user_agent;
  protected $remote_address;

  function __construct($server, $get = array(), $post = array(), $primary_request_parameter = 'q') {

    if(isset($get[$primary_request_parameter])) {
      $this->setArgs($get[$primary_request_parameter]);
      $this->setUri($get[$primary_request_parameter]);
      unset($get[$primary_request_parameter]);
    }

    $this->parseServerAttributes($server);
    $this->setParameters($get);
    $this->setParameters($post);
  }

  /**
   * @param mixed $base_url
   */
  public function setBaseUrl($base_url)
  {
    $this->base_url = $base_url;
  }

  /**
   * @return mixed
   */
  public function getBaseUrl()
  {
    return $this->base_url;
  }

  /**
   * @return mixed
   */
  public function getRequestMethod()
  {
    return $this->request_method;
  }

  /**
   * @param mixed $request_method
   */
  public function setRequestMethod($request_method)
  {
    $this->request_method = $request_method;
  }

  /**
   * @param mixed $port
   */
  public function setPort($port)
  {
    $this->port = $port;
  }

  /**
   * @return mixed
   */
  public function getPort()
  {
    return $this->port;
  }

  /**
   * @param mixed $protocol
   */
  public function setProtocol($protocol)
  {
    $this->protocol = $protocol;
  }

  /**
   * @return mixed
   */
  public function getProtocol()
  {
    return $this->protocol;
  }

  /**
   * @param mixed $query_string_raw
   */
  public function setQueryStringRaw($query_string_raw)
  {
    $this->query_string_raw = $query_string_raw;
  }

  /**
   * @return mixed
   */
  public function getQueryStringRaw()
  {
    return $this->query_string_raw;
  }

  /**
   * @param mixed $remote_address
   */
  public function setRemoteAddress($remote_address)
  {
    $this->remote_address = $remote_address;
  }

  /**
   * @return mixed
   */
  public function getRemoteAddress()
  {
    return $this->remote_address;
  }

  /**
   * @param mixed $uri
   */
  public function setUri($uri)
  {
    $this->uri = $uri;
  }

  /**
   * @return mixed
   */
  public function getUri()
  {
    return $this->uri;
  }

  /**
   * @param mixed $request_time
   */
  public function setRequestTime($request_time)
  {
    $this->request_time = $request_time;
  }

  /**
   * @return mixed
   */
  public function getRequestTime()
  {
    return $this->request_time;
  }

  /**
   * @param mixed $user_agent
   */
  public function setUserAgent($user_agent)
  {
    $this->user_agent = $user_agent;
  }

  /**
   * @return mixed
   */
  public function getUserAgent()
  {
    return $this->user_agent;
  }

  protected function parseServerAttributes($server) {
    $this->protocol = ((!empty($server['HTTPS']) && $server['HTTPS'] == 'on') ? "https" : "http");
    $this->setBaseUrl($server['SERVER_NAME']);
    $this->setPort($server['SERVER_PORT']);
    $this->setRequestTime($server['REQUEST_TIME']);
    $this->setRequestMethod($server['REQUEST_METHOD']);
  }

  protected function sanitize($string) {
    return filter_var($string, FILTER_SANITIZE_URL);
  }


  protected function setArgs($args) {
    $args = explode('/', $args);
    foreach($args as $arg) {
      $this->addArg($arg);
    }
  }

  protected function getArgs() {
    return $this->query_arguments;
  }

  protected function addArg($arg) {
    $this->query_arguments[] = $this->sanitize($arg);
  }

  public function arg($i) {
    return $this->query_arguments[$i];
  }

  protected function addParameter($name, $value) {
    $this->parameters[$this->sanitize($name)] = $this->sanitize($value);

  }

  protected function setParameters($parameters) {
    foreach($parameters as $parameter => $value) {
      $this->addParameter($parameter, $value);
    }
  }

  protected function getParameter($parameter) {
    return $this->parameters[$parameter];
  }
}