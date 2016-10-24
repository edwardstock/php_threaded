//
// Created by Eduard Maximovich <edward.vstock@gmail.com>.
//


#include <cstdint>
#include <phpcpp.h>
#include <iostream>
#include <mutex>
#include <utility>
#include <type_traits>
#include <php.h>
#include <thread>
#include <phpcpp/tsrm.h>

#ifndef PHP_THREADED_PHPCALLBACK_H
#define PHP_THREADED_PHPCALLBACK_H

using namespace std;

class PhpCallback : public Php::Base
{
    int64_t id;
    int64_t priority = 0;
    Php::Value callback;
    Php::Value result;
    Php::Value futureFunction;
    std::mutex locker;

    friend class Workable;

public:
    typedef std::shared_ptr<PhpCallback> Ptr;

    struct Priority
    {
        bool operator()(const PhpCallback::Ptr &left, const PhpCallback::Ptr &right) const
        {
            return left->getPriority() < right->getPriority();
        }
    };

    /**
     * Constructor
     * @param id
     * @param callback
     * @param priority
     * @return
     */
    PhpCallback(const int64_t id, const Php::Value userCallback);

    /**
     * Destructor
     */
    ~PhpCallback()
    {
        this->destruct();
    };

    void __destruct() const
    {
        this->destruct();
    }

    /**
     * @return const id value
     */
    Php::Value getId() const
    {
        return Php::Value(id);
    }

    /**
     * @return const priority in priority queue
     */
    Php::Value getPriority() const
    {
        return Php::Value(priority);
    }

    Php::Value getResult() const
    {
        return result;
    }

    /**
     * Queue priority
     * @param priority
     */
    void setPriority(int64_t priority);

    /**
     * Future callback function
     * @param params
     */
    void setFuture(Php::Parameters &params);

private:
    void destruct() const
    {
    }
    void setResult(Php::Value value = nullptr);

    void call();

    void callFuture();
};

#endif //PHP_THREADED_PHPCALLBACK_H
