//
// Created by Eduard Maximovich <edward.vstock@gmail.com>.
//

#include <thread>
#include "PhpCallback.h"

PhpCallback::PhpCallback(const int64_t id, const Php::Value callback) {
	this->id = id;
	this->callback = std::move(callback);
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
#ifdef ZEND_DEBUG
	cout << "THREAD ID: " << std::this_thread::get_id() << endl;
#endif
	try {
		this->setResult(this->callback());
	} catch (std::exception &e) {
		cerr << "Cannot run callback " << e.what() << endl;
	}
}

void PhpCallback::callFuture() {
	if (this->futureFunction) {
		this->futureFunction(getResult());
	}
}
