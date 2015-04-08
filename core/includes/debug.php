<?php

function pre($data) {
  return '<pre>'.print_r($data, TRUE).'</pre>';
}