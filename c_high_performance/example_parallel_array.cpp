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
template<class T> auto sum_scores(const std::vector<T> & objects) {
	ScopedTimer t{"sum_scores"};

	auto sum = 0;
	for (const auto& obj: objects) {
		sum +=obj.score_;
	}
	return sum;
}
int main () {

	auto small_objects = std::vector<SmallObject>(1'000'000);
	auto big_objects = std::vector<BigObject>(1'000'000);

	std::cout << sizeof(SmallObject);
	std::cout << sizeof(BigObject);
	auto sum = 0;
	sum += sum_scores(small_objects);
	sum += sum_scores(big_objects);

}
