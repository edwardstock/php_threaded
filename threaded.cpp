//
// Created by Eduard Maximovich <edward.vstock@gmail.com>.
//
#include <iostream>
#include <phpcpp.h>
#include <thread>
#include <queue>
#include <condition_variable>
#include "classes/Workable.h"

#ifndef ZTS
#error "TSRM is not available. Please, compile your php with --enable-maintainer-tsrm flag"
#endif

using namespace std;

// Symbols are exported according to the "C" language
extern "C"
{

// export the "get_module" function that will be called by the Zend engine
PHPCPP_EXPORT void *get_module() {
	// create extension
	static Php::Extension extension("threaded", "0.1");


	Php::Class<Workable> workable("Workable");
	workable.constant("HARDWARE_CONCURRENCY", (int32_t) std::thread::hardware_concurrency());

	workable.method<&Workable::run>("run");
	workable.method<&Workable::add>("add", {
		Php::ByVal("func", Php::Type::Callable, true),
		Php::ByVal("priority", Php::Type::Numeric, false)
	});
	extension.add(std::move(workable));

	Php::Class<PhpCallback> future("CallbackFuture");
	future.method<&PhpCallback::setFuture>("future", {
		Php::ByVal("func", Php::Type::Callable, true)
	});

	future.method<&PhpCallback::getPriority>("getPriority");
	future.method<&PhpCallback::getId>("getId");
	extension.add(std::move(future));

	// return the extension module
	return extension.module();
}
}


