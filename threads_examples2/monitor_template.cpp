#include <queue>
#include <mutex>
#include <condition_variable>
#include <atomic>
#include <chrono>
#include <iostream>

class Monitor {
	private:
		std::mutex mut;
		
	public:
		virtual void run() = 0;
		virtual void operator()() {
			std::lock_guard<std::mutex> lk(mut);
			run();
		};
		virtual ~Monitor() {};
};

class DoSomething1: public Monitor {
	public:
		DoSomething1(): Monitor() {};
		void run () {
			std::cout << "-----------------------Doing something---------------------" << '\n';
		};
		~DoSomething1() {};
};

int main () {
	DoSomething1 something1;
	something1();
	return 0;
}
