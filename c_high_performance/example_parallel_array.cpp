#include <iostream>
#include <array>
#include <cstdlib> 

struct SmallObject {
	SmallObject(): score_{std::rand()} {}
	std::array<char, 4> data_{};
	int score_{};
};

struct BigObject {
	BigObject(): score_{std::rand()} {}
	std::array<char, 256> data_{};
	int score_{};
};
int main () {
	std::cout << sizeof(SmallObject);
	std::cout << sizeof(BigObject);

}
