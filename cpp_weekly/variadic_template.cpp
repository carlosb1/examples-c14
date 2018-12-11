#include <sstream>
#include <iostream>
#include <vector>

template <typename T> std::string to_string_impl(const T& t) {
	std::stringstream ss;
	ss << t;
	return ss.str();
}
std::vector<std::string> to_string() {
	return {};
}

template <typename ...Param>
std::vector<std::string> to_string(const Param& ... param) {
	return {to_string_impl(param)...};
}

int main () {
	const auto vec = to_string("hello", 1, 5.3);
	for (const auto &o: vec) {
		std::cout << o << "\n";
	}	
	std::cout << to_string_impl(1) << '\n';
	to_string_impl("hello world");
	to_string_impl(5.3);
}

