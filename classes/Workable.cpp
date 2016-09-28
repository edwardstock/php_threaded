//
// Created by Admin on 28.09.16.
//

#include "Workable.h"

void Workable::runner(PhpCallback cb) {
	results.push_back(cb.callback());

	locker.lock();
	done++;
	locker.unlock();
}

void Workable::add(Php::Parameters &params) {
	if (params.size() < 1) {
		return;
	}

	PhpCallback cb;
	cb.callback = params[0];
	if (params.size() == 2) {
		cb.priority = params[1];
	}

	callbacks.push(cb);
	total++;
}

void Workable::setFuture(Php::Parameters &params) {
	if (params.size() < 1) {
		return;
	}

	future = params[0];
}

void Workable::run() {
	results.clear();

	if (callbacks.empty()) {
		return;
	}

	while (!callbacks.empty()) {
		//locker.lock();
		std::thread t(&Workable::runner, this, callbacks.top());
		callbacks.pop();
		cout << "Started worker" << endl;
		t.detach();
		//locker.unlock();
	}

	// wait until last thread did not finished
	while (done < total) {
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}

	if (future) {
		future(getResults());
	}

	done = 0;
	total = 0;
}