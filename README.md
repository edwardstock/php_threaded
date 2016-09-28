# php_threaded
Async php code execution with callback

## Building

* Download and compile stable version of PHP-CPP https://github.com/CopernicaMarketingSoftware/PHP-CPP
* If library is successfully compiled and installed, do next:
```bash
git clone https://github.com/edwardstock/php_threaded.git
cd php_threaded
make
make install
```

* Then check extension is installed: `php -m | grep threaded`