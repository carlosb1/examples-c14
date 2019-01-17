#include <functional>
#include <iostream>



/*
void print(int i, const std::string &s) {
	std::cout << i << ' '<< s << "\n";
}
*/

template <typename T> void print(T i, const std::string &s) {
	std::cout << i << " " << s << "\n";
}

int main () {
	int i = 5;
	//const auto f = std::bind(&print, i);
	//const auto f = std::bind(&print, std::ref(i), std::placeholders::_1);
	const auto f = std::bind(&print<int>, std::placeholders::_2, std::placeholders::_1);
	f("hello",i);
	i = 6;
	f("world",i);
	std::function<void (const std::string &, int)> f2(f);
	f2("test", i);
}
