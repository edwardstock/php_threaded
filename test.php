<?php
function myFunction() {
	return 'some_value';
}


$w = new Workable();

$q   = 1;
$out = [];
$dl  = function () {
    return myFunction();
};

$future = function($result) use(&$out, &$q) {
    echo "Downloaded {$q}\n";
    $out[] = $result;
    $q++;
};


$w->add($dl, 5)->future($future);
$w->add($dl, 10)->future($future);
$w->add($dl, 30)->future($future);
$w->add($dl, 40)->future($future);


echo "\n == Async ==\n";
$t = microtime(true);
$w->run();

$t = microtime(true) - $t;
echo "\nTime spent: " . ($t * 1000) . " ms\n";
echo sizeof($out) . PHP_EOL;

echo "\n == Sync ==\n";

$t   = microtime(true);
$cnt = 4;
for ($i = 0; $i < $cnt; $i++) {
    //file_get_contents('https://google.com');
}
$t = microtime(true) - $t;
echo "\nTime spent: " . ($t * 1000) . " ms\n";