<?php

//TODO: Convert to .ini file.
$registry = Registry::getInstance();

$registry->setting('db_host', 'localhost');
$registry->setting('db_user', 'magus');
$registry->setting('db_pass', 'magus_user');
$registry->setting('db_name', 'magus');

$registry->setting('admin_url', 'admin');
$registry->setting('theme', 'default');
$registry->setting('admin_path', 'admin');

$registry->setting('unique_email', TRUE);
