#include "threadsafe_queue2.h"
#include <thread>
#include <iostream>

class Runnable {
	public:
		virtual void operator()()  = 0;
		virtual ~Runnable() {};
};

class DoSomething1: public Runnable {
	public:
		DoSomething1() {};
		void operator()() {
			std::cout << "-----------------------Doing something---------------------" << '\n';
		};
		~DoSomething1() {};
};

class DoSomething2: public Runnable {
	public:
		DoSomething2() {};
		void operator()() {
			std::cout << "-----------------------Doing something 2---------------------" << '\n';
		};
		~DoSomething2() {};
};



class ActiveObject {
	private:
		threadsafe_queue<Runnable*> queue;
		DoSomething1 doOper;
		DoSomething2 doOper2;
		std::vector<std::thread> threads;
	public:
		ActiveObject() {};
		void run () {
			while (!queue.empty()) {
				std::shared_ptr<Runnable*> runnable = queue.wait_and_pop();
				Runnable *executable =*runnable.get();
				std::thread t1(&Runnable::operator(),executable);
				threads.push_back(std::move(t1));
			}
		}
		inline void doSomething() {
			queue.push(&doOper);
					
		}

		inline void doSomething2() {
			queue.push(&doOper2);
		}

		inline void waitAllFinished() {
			for(int i = 0; i < (int)threads.size(); i++) {
				threads.at(i).join();
			}
		}

};

int main () {
	ActiveObject activeObject;
	activeObject.doSomething();
	activeObject.doSomething2();
	activeObject.doSomething2();
	activeObject.doSomething();
	activeObject.doSomething();
	activeObject.run();
	activeObject.waitAllFinished();
	
	

}
