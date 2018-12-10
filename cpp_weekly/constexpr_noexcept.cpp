#include <iostream>
// constexpr -> specifies that the value of a variable of function can appear in 
// noexcept  -> 
constexpr int add(const int lhs, const int rhs) noexcept {
	return lhs + rhs;
}

constexpr int multiply(const int lhs, const int rhs) noexcept{
	return lhs + rhs;
}

auto calc(const int val1, const int val2, const int val3) {
	return add(val1, multiply(val2, val3));
}
int main() {
	std::cout << calc(1,2,4) << "\n";
}
