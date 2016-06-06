#include "synchronized.h"
#include <unordered_map>
#include <iostream>

int main () {
	synchronized <std::unordered_map<int,int>> m;

	m.write( [&] (auto &&m) {
			m[1] = 2;
			m[42] = 13;
			});

	m.read ( [&](auto&&m) {
		for (auto&& x:m) {
			std::cout << x.first << "->" << x.second << "\n";
		}
	});

	bool empty = m.read([&](auto&&m) {
			return m.empty();
		});

	std::cout << empty << "\n";
	auto copy = m.copy();
	std::cout << copy.empty() << "\n";

	synchronized < std::unordered_map<int,int>> m2 = m;
	m2.read ([&](auto&&m) {
		for (auto && x:m) {
			std::cout << x.first << "->" << x.second << "\n";
		}

	});

}
