//
// Created by root on 15.10.2016.
//


#ifndef PHP_THREADED_THREADED_H
#define PHP_THREADED_THREADED_H

#include <iostream>
#include <phpcpp.h>
#include <thread>
#include <queue>
#include <condition_variable>
#include <php.h>
#include "classes/Workable.h"
#include "classes/ThreadPool.cpp"

#define PHP_THREADED_EXTVER "0.1"
#define PHP_THREADED_EXTNAME "threaded"

#ifndef ZTS
#error "threaded requires that Thread Safety is enabled, add --enable-maintainer-zts to your PHP build configuration"
#endif

#include <TSRM.h>

int threaded_globals_id;
typedef struct _zend_threaded_globals
{
} zend_threaded_globals;

ZEND_EXTERN_MODULE_GLOBALS(threaded)
#endif //PHP_THREADED_THREADED_H
