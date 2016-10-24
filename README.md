# php_threaded
Async php code execution with futures (in development, very unstable now)

## Building

* Download and compile [forked PHP-CPP](https://github.com/edwardstock/PHP-CPP)
* If library is successfully compiled and installed, do next:
```bash
git clone https://github.com/edwardstock/php_threaded.git
cd php_threaded
make
make install

// installing default looks to php ini autoload path: /etc/php.d
// if you have different path, set it to arg: 
make install inidir=/your/php/php.d
// or manually just add to your php.ini: 
echo "extension=threaded.so" >> /path/to/php.ini
```

* Then check extension is installed: `php -m | grep threaded`


## Usage

```php
<?php

// creating job function
$jobFunction = function(){
    return file_get_contents('http://exmample.com');
};

// creating future success function
$success = function($result) {
    file_put_contents('/tmp/example_com.html', $result, mb_strlen($result, '8bit'));
};

// instance of thread manager
$workable = new \Workable();

for($i = 0; $i < 10; $i++) {
    // adding tasks to priority queue
    $workable->add($jobFunction, $priority = 10)->future($success);
}

// run added jobs
$workable->run();

// Profit! But not yet (thx to php developers)

```

## Why not working and what need to do to get working extension
 - why
    1. Very poor and deprecated PHP ZTS (TSRM) documentation and php nothings doing to make transparent multi-threaded usage of user defined data (like global executors, global compilers, file loaders, etc)
    2. Memory management
    
 - todo
    1. Copy user defined data to local storage
    2. Test PHP-CPP lib by memory management, cause hard to catch double freeing variables or vise versa creating not persistent string pointers that dies when u try to use it in new thread (see php emalloc) 