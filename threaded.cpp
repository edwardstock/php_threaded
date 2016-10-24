//
// Created by Eduard Maximovich <edward.vstock@gmail.com>.
//

#include "threaded.h"

// Symbols are exported according to the "C" language
extern "C"
{

// export the "get_module" function that will be called by the Zend engine
PHPCPP_EXPORT void *get_module()
{
    // create extension
    static Php::Extension extension(PHP_THREADED_EXTNAME, PHP_THREADED_EXTVER);

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


