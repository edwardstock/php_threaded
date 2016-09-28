#include <iostream>
#include <phpcpp.h>
#include <thread>
#include <queue>
#include <condition_variable>
#include "classes/Workable.h"

using namespace std;

// Symbols are exported according to the "C" language
extern "C"
{

// export the "get_module" function that will be called by the Zend engine
PHPCPP_EXPORT void *get_module() {
	// create extension
	static Php::Extension extension("threaded", "1.0");


	Php::Class<Workable> tWorker("Workable");
	tWorker.constant("HARDWARE_CONCURRENCY", (int32_t) std::thread::hardware_concurrency());

	tWorker.method<&Workable::run>("run");
	tWorker.method<&Workable::add>("add", {
		Php::ByVal("func", Php::Type::Callable, true),
		Php::ByVal("priority", Php::Type::Numeric, false)
	});
	tWorker.method<&Workable::setFuture>("setFuture", {
		Php::ByVal("func", Php::Type::Callable, true)
	});


	extension.add(std::move(tWorker));

	// return the extension module
	return extension.module();
}
}


