<?php
error_reporting(E_ALL | E_NOTICE);
ini_set('display_errors', 'on');

$a = 0;
$cb = function()use($a){
	throw new \Exception('test');
	return 1;
};
$q = 'a';
echo testCalling($cb);

unset($q);




