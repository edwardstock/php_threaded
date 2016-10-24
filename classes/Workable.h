//
// Created by Eduard Maximovich <edward.vstock@gmail.com>.
//

#include <iostream>
#include <phpcpp.h>
#include <thread>
#include <queue>
#include <condition_variable>
#include <map>
#include "PhpCallback.h"

#ifndef PHP_THREADED_WORKABLE_H
#define PHP_THREADED_WORKABLE_H

using namespace std;

class Workable : public Php::Base
{
    int64_t lastId = 1;
    int64_t total = 0;

    std::priority_queue<
        PhpCallback::Ptr,
        std::vector<PhpCallback::Ptr>,
        PhpCallback::Priority
    > callbacks;

    std::mutex locker;

    PhpCallback::Ptr runner(PhpCallback::Ptr);

public:
    Workable() : Base() {}
    ~Workable() {}
    void __destruct() const {}

    Php::Value add(Php::Parameters &params);
    void run();
};

#endif //PHP_THREADED_WORKABLE_H
