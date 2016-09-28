<?php
/*
class Workable
{
	const HARDWARE_CONCURRENCY = 2; // number of available hardware threads

	public function add($func, $priority = 0) {
		// adds new job
	}

	public function run() {
	}

	public function setFuture($callback) {
	}
}
*/

$w = new \Workable();
$w->setFuture(function($results){
	var_dump($results);
});

$w->add(function(){
	$c = file_get_contents('https://google.com');
	echo "Downloaded 1\n";
	return $c;
}, 5);

$w->add(function(){
	$c = file_get_contents('https://google.com');
    	echo "Downloaded 2\n";
    	return $c;
}, 10);

$w->add(function(){
	$c = file_get_contents('https://google.com');
    	echo "Downloaded 3\n";
    	return $c;
}, 30);

$w->add(function(){
	$c = file_get_contents('https://google.com');
    	echo "Downloaded 4\n";
    	return $c;
}, 40);



$t = microtime(true);
$w->run();
$t = microtime(true) - $t;
echo "\nTime spent: ". ($t * 1000)." ms\n";