#include <iostream>
#include <mutex>
class Singleton {
	public:
		static Singleton *instance (void) {
			if (!instance_) { 
				//critical section 
				std::lock_guard<std::mutex> lk(mut);
				if (!instance_) {	
					instance_ = new Singleton;
				}


			}
			return instance_;
		}
		void method() {
			std::cout << "do method\n";
		}
	private:
		static std::mutex mut;
		static Singleton *instance_;

};
Singleton* Singleton::instance_;
std::mutex Singleton::mut; 

int main () {
	std::cout << "Trying to execute the code\n";
	Singleton::instance()->method();
}
