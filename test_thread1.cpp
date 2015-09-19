#include <iostream>
#include <thread>
void hello () {
	std::cout << "Hello Concurrent World\n" << std::endl;

}

int main () {
	std::thread t(hello);
	t.join();
}

