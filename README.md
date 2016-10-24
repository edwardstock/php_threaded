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