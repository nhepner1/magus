<?php

//TODO: Convert to .yaml file.
$registry = Registry::getInstance();

// Database settings
$registry->setting('db_host', 'localhost');
$registry->setting('db_user', 'magus');
$registry->setting('db_pass', 'magus_user');
$registry->setting('db_name', 'magus');

// Application settings
$registry->setting('admin_url', 'admin');
$registry->setting('theme', 'default');
$registry->setting('admin_path', 'admin');
$registry->setting('unique_email', TRUE);

// Sessions
$registry->setting('session_name', 'magus_secure_session');
$registry->setting('secure_connections_only', FALSE); // If TRUE, only send session cookies over TLS. Requires TLS enabled.

// Authentication settings
$registry->setting('password_salt', 'ThmpLxkeZAKTjcmp5ITn');
$registry->setting('hash_algorithm', 'sha512');
