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