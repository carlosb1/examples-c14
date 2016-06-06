#include <iostream>
#include <thread>
#include "thread_guard.h"


/* function to execute */
struct func
{
	int& i;
	
	func (int& i_): i(i_){}

	void operator()()
	{
		for (unsigned j=0; j <1000000; ++j) {
			do_something(j);
		}
	}
	void do_something(int value) {
		std::cout << "Doing something value="<<value<<std::endl;
	}
};

void do_something_in_current_thread() {
	for (unsigned i=0; i <1000000; ++i) {
			std::cout << "doing something new in current thread "<<i<<std::endl;
	}
}


int main () {
	int some_local_state = 0;
	func my_func(some_local_state);
	std::thread t(my_func);
	ThreadGuard g(t);
	do_something_in_current_thread();
}

