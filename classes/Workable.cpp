//
// Created by Eduard Maximovich <edward.vstock@gmail.com>.
//

#include <future>
#include "Workable.h"
#include "ThreadPool.cpp"

PhpCallback::Ptr Workable::runner(PhpCallback::Ptr cb)
{
    Php::Thread::prepare();
    cb->call();
    return cb;
}

Php::Value Workable::add(Php::Parameters &params)
{
    if (params.size() < 1) {
        return Php::Value(nullptr);
    }

    locker.lock();
    PhpCallback::Ptr cb = std::make_shared<PhpCallback>(lastId, params.at(0));
    if (params.size() == 2) {
        cb->setPriority(params.at(1));
    }

    callbacks.push(cb);
    total++;
    lastId++;
    locker.unlock();

    return Php::Object("CallbackFuture", cb.get());
}

void Workable::run()
{
    if (callbacks.empty()) {
        return;
    }

    std::vector<std::future<PhpCallback::Ptr >> results;

    if (callbacks.size() == 1) {
        callbacks.top()->call();
        callbacks.top()->callFuture();
        callbacks.pop();

        total = 0;
        results.clear();
        return;
    }

    ThreadPool pool(callbacks.size());

    while (!callbacks.empty()) {
        results.emplace_back(
            pool.enqueue(&Workable::runner, this, callbacks.top())
        );
        callbacks.pop();
    }

    for (auto &&result: results) {
        result.get()->callFuture();
    }

    total = 0;
    results.clear();
}