//
// Created by Eduard Maximovich <edward.vstock@gmail.com>.
//

#include <future>
#include "Workable.h"
#include "ThreadPool.cpp"

PhpCallback *Workable::runner(PhpCallback *cb) {
	cb->call();
	return cb;
}

Php::Value Workable::add(Php::Parameters &params) {
	if (params.size() < 1) {
		return Php::Value(nullptr);
	}

	locker.lock();
	const Php::Value phpCallback = params[0].clone();
	PhpCallback *cb = new PhpCallback(lastId, phpCallback);
	if (params.size() == 2) {
		cb->setPriority(params[1]);
	}

	callbacks.push(cb);
	total++;
	lastId++;
	locker.unlock();

	return Php::Object("CallbackFuture", cb);
}

void Workable::run() {
	if (callbacks.empty()) {
		return;
	}

	ThreadPool pool(callbacks.size());
	std::vector<std::future<PhpCallback *>> results;

	while (!callbacks.empty()) {
		results.emplace_back(
			pool.enqueue(&Workable::runner, this, callbacks.top())
		);

		callbacks.pop();
	}

	locker.lock();
	for (auto &&result: results) {
		PhpCallback *cb = result.get();
		cb->callFuture();
	}
	locker.unlock();


	results.clear();
	total = 0;
}