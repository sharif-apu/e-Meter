<?php
require '../vendor/autoload.php';

$app = new \Slim\Slim([
'view'=> new \Slim\Views\Twig()
  

]);
//Database Configuration
$app->container->singleton('db', function(){
	
	return new PDO('mysql:host=127.0.0.1;dbname=powercost','root','');
	
});

$view=$app->view();
$view->setTemplatesDirectory('../app/views');
$view->parserExtensions=[
new \Slim\Views\TwigExtension()

];
require 'routes.php';


$app->run();  
