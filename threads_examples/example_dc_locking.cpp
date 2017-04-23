#include <iostream>
class Singleton {
	public:
		static Singleton *instance (void) {
			if (!instance_) 
				//critical section 
				instance_ = new Singleton;
			return instance_;
		}
		void method() {
			std::cout << "do method\n";
		}
	private:
		static Singleton *instance_;

};
Singleton* Singleton::instance_;


int main () {
	std::cout << "Trying to execute the code\n";
	Singleton::instance()->method();
}
