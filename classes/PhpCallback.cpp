//
// Created by Eduard Maximovich <edward.vstock@gmail.com>.
//

#include "PhpCallback.h"

PhpCallback::PhpCallback(const int64_t id, const Php::Value userCallback)
{
    this->id = id;
    this->callback = userCallback.clone();
    this->futureFunction = Php::Value(nullptr);
}

void PhpCallback::setPriority(int64_t priority)
{
    this->priority = priority;
}

void PhpCallback::setFuture(Php::Parameters &params)
{
    this->futureFunction = params[0];
}

void PhpCallback::setResult(Php::Value value)
{
    this->result = value;
}

void PhpCallback::call()
{
    if (!this->callback.isObject() || !this->callback.instanceOf("\\Closure")) {
        return;
    }

    try {
        this->setResult(this->callback().clone());
    } catch (std::exception &e) {
        this->setResult(Php::Value(nullptr));
        cerr << "Cannot run job, cause: " << e.what() << endl;
    }
}

void PhpCallback::callFuture()
{
    if (!this->futureFunction.isObject() || !this->futureFunction.instanceOf("\\Closure")) {
        return;
    }

    try {
        this->futureFunction(this->getResult());
    } catch (std::exception &e) {
        this->setResult(Php::Value(nullptr));
        cerr << "Cannot run future, cause: " << e.what() << endl;
    }
}
