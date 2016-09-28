#include <iostream>
#include <phpcpp.h>
#include <thread>
#include <queue>
#include <condition_variable>

#ifndef PHP_THREADED_WORKABLE_H
#define PHP_THREADED_WORKABLE_H

using namespace std;

class Workable : public Php::Base {
	struct PhpCallback {
		Php::Value callback;
		int64_t priority = 0;
	};

	struct CallbackPriority {
		bool operator()(const PhpCallback &left, const PhpCallback &right) {
			return left.priority < right.priority;
		}
	};

	size_t done = 0;
	size_t total = 0;

	std::priority_queue<PhpCallback, std::vector<PhpCallback>, CallbackPriority> callbacks;
	std::mutex locker;

	std::vector<Php::Value> results;
	Php::Value future = 0;

	void runner(PhpCallback cb);

public:
	Workable() : Base() {}

	virtual ~Workable() = default;

	void run();

	void add(Php::Parameters &params);

	void setFuture(Php::Parameters &params);

	Php::Value getResults() {
		return Php::Value(results);
	}
};


#endif //PHP_THREADED_WORKABLE_H
