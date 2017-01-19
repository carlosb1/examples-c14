#include "threadsafe_queue2.h"
#include <thread>
#include <chrono>
#include <iostream>
#include <future>

struct Result {
	const bool status;
	const std::string operation;
	const std::string result;
	Result (bool status_, std::string operation_, std::string result_): 
			status(status_), operation(operation_), result(result_) {}; 

};


class Asynctask {
	private:
		std::shared_ptr<threadsafe_queue<Result>> sharedQueue;
	public:
		Asynctask(std::shared_ptr<threadsafe_queue<Result>> & sharedQueue_): sharedQueue(sharedQueue_) {};
		virtual Result run () = 0;

		void operator()() {
			auto handle = std::async(std::launch::async,&Asynctask::run,this);
			sharedQueue->push(handle.get());
		}
};


class Synctask {
	public:
		Synctask(std::shared_ptr<threadsafe_queue<Result>>  sharedQueue_): sharedQueue(sharedQueue_), finish(false) {}
		inline void end() {
			finish = true;
		}
		void operator () ()  {
			while (!finish) {
				std::shared_ptr<Result> result  = sharedQueue->wait_and_pop();
				onResult(result);
			}	
		}
	private:
		std::shared_ptr<threadsafe_queue<Result>> sharedQueue;
		bool finish;
		virtual void onResult (std::shared_ptr<Result> result)  = 0;

};

class Synctask1: public Synctask {
	public:
		Synctask1 (std::shared_ptr<threadsafe_queue<Result>> & sharedQueue_): Synctask(sharedQueue_) {};
		void onResult (std::shared_ptr<Result> result) {
			std::cout << "Syntask1! read: status="<<result->status<<" operation=" <<result->operation << " result="<<result->result<<'\n';
		}
};
class Synctask2: public Synctask {
	public:
		Synctask2 (std::shared_ptr<threadsafe_queue<Result>> & sharedQueue_): Synctask(sharedQueue_) {};
		void onResult (std::shared_ptr<Result> result) {
			std::cout << "Syntask2! read: status="<<result->status<<" operation=" <<result->operation << " result="<<result->result<<'\n';
		}
};



class Asyntask1: public Asynctask  {
		public:
			Asyntask1 (std::shared_ptr<threadsafe_queue<Result>> & sharedQueue_): Asynctask(sharedQueue_) {};
			Result run ()  {
				std::cout << "Asyntask1\n";
				Result result(true, std::string("firstOper"),std::string("Ok"));	
				std::this_thread::sleep_for(std::chrono::seconds(2));
				return result;
			}	
};


class Asyntask2: public Asynctask  {
		public:
			Asyntask2 (std::shared_ptr<threadsafe_queue<Result>> & sharedQueue_): Asynctask(sharedQueue_) {};
			Result run ()  {
				std::cout << "Asyntask2\n";
				Result result(true, std::string("secondOper"),std::string("Fails"));	
				std::this_thread::sleep_for(std::chrono::seconds(4));
				return result;
			}	
};


class Asyntask3: public Asynctask  {
		public:
			Asyntask3 (std::shared_ptr<threadsafe_queue<Result>> & sharedQueue_): Asynctask(sharedQueue_) {};
			Result run ()  {
				std::cout << "Asyntask3\n";
				Result result(true, std::string("thirdOper"),std::string("Fails"));	
				std::this_thread::sleep_for(std::chrono::seconds(1));
				return result;
			}	
};

int main () {
	std::shared_ptr<threadsafe_queue<Result>> queue = std::make_shared<threadsafe_queue<Result>>();
	Synctask1 sync1(queue);
	Synctask2 sync2(queue);

	std::thread t1(&Synctask::operator(),sync1);
	std::thread t2(&Synctask::operator(),sync2);
	
	Asyntask1 async1(queue);
	Asyntask2 async2(queue);
	Asyntask3 async3(queue);
	async1();
	async2();
	async3();

	std::this_thread::sleep_for(std::chrono::seconds(7));
	

	sync1.end();
	sync2.end();
	
}
