#ifndef _THREAD_POOL_EXAMPLE_HPP_
#define _THREAD_POOL_EXAMPLE_HPP_
#ifdef __cplusplus

#include "threadpool.hpp"

using namespace astp;

/**
*	The ThreadPool instance used by
*	the following example functions.
*/
ThreadPool tp = ThreadPool(4);




void 
simple_func() {
	std::cout << "I'm a func called async" << std::endl;
}

void 
example_global_func(int number_of_calls) {
	for (int i = 0; i < number_of_calls; i++) {
		tp.push([] () {
			simple_func();
		});
	}
	tp.wait();
}



void 
example_inline_code(int number_of_calls) {
	for (int i = 0; i < number_of_calls; i++) {
		tp.push([] () {
			std::vector<int> vec;
			for (int k = 0; k < 1000; k++) {
				vec.push_back(k);
				std::cout << vec.size() << std::endl;
			}
		});
	}
	tp.wait();
}



class JobTest
{
public:
	void 
	do_something(int i) const {
		std::cout << "The magic number is: " << i << std::endl;
	}	
};

void
example_member_function(int number_of_calls) {
	auto job = JobTest();
	tp.resize(1);
	for (int i = 0; i < number_of_calls; i++) {
		tp.push([job, i] () {
			job.do_something(i);
		});
	}
	tp.wait();
}




#endif // __cplusplus
#endif // _THREAD_POOL_EXAMPLE_HPP_
