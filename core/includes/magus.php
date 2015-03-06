<?php

// Initialize session and provide arguments.
$session = new Session();
$session->setSessionName($registry->setting('session_name'))
  ->setSecureConnectionsOnly($registry->setting('secure_connections_only'))
  ->startSession();

$dbconnect = DBconnect::getInstance();
$dbconnect->connect('main',
  $registry->setting('db_host'),
  $registry->setting('db_user'),
  $registry->setting('db_pass'),
  $registry->setting('db_name'),
  TRUE
);

// Initiate form handling
if($_POST) {

    //TODO: Create observer for registered forms to identify and process post requests
    if($_POST['username'] && $_POST['password']) {

        $auth = new Authentication(new DBQuery($dbconnect), $_POST['username'], $_POST['password']);

        $userauth = $auth->authenticateUser();
        if($userauth){
          $user = new User(new DBQuery($dbconnect));
          $user->load($userauth['id']);
          $_SESSION['user'] = $user;
        }
    }
}



if($session->isValidSession()) {
    $content = "You are logged in!";
} else {
    $block = new Block();
    $block->setTemplate(THEMES_PATH."/default/login.tpl.php");
    $content = $block->render();
}

$page = new Page();
$page->setTitle('Magus v2.0: Electric Boogaloo');
$page->setTheme($registry->setting('theme') ? $registry->setting('theme') : 'default');
$page->setRegion('header', "Magus v2.0: Electric Boogaloo");
$page->setRegion('left_sidebar', "Tada!!!");
$page->setRegion('right_sidebar', "Wicked");
$page->setRegion('footer', "<a href='logout'>Logout</a>");

$dbquery = new DBQuery($dbconnect->connection());
$dbquery->executeQuery("SELECT * FROM users");

$page->setRegion('content', $content);
print $page->render();