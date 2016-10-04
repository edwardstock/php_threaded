//
// Created by Eduard Maximovich <edward.vstock@gmail.com>.
//

#include "PhpCallback.h"

PhpCallback::PhpCallback(const int64_t id, const Php::Value callback) {
	this->id = id;
	this->callback = callback;
	this->priority = priority;
}

void PhpCallback::setPriority(int64_t priority) {
	this->priority = priority;
}

void PhpCallback::setFuture(Php::Parameters &params) {
	this->futureFunction = params[0];
}

void PhpCallback::setResult(Php::Value value) {
	this->result = value;
}

void PhpCallback::call() {
	locker.lock();
	try {
		this->setResult(
			Php::call("call_user_func", this->callback)
		);
	} catch (std::exception &e) {
		cerr << "Cannot run callback " << e.what() << endl;
	}

	locker.unlock();
}

void PhpCallback::callFuture() {
	if (this->futureFunction) {
		this->futureFunction(getResult());
	}
}
