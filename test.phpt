<?php
error_reporting(E_ALL | E_NOTICE);
ini_set('display_errors', 'on');


$func = function() {
	return "Test".random_int(1, 100);
};
$w = new \Workable();



$success = function($result) {
	var_dump($result);
};

for($i = 0; $i < 2; $i++) {
	$w->add($func, 10)->future($success);
}

$w->run();


