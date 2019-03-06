#include <iostream>
#include <vector>
#include <algorithm>

int main () {
	int rows = 4;
	int cols = 4;
	
	std::vector<std::vector<int>> matrix(rows);
	auto func_init = [cols](auto vec) { 
		std::cout << "hello!";
		vec.assign(cols,0); };
	for_each(matrix.begin(), matrix.end(), func_init);

	for (auto rows: matrix) {
		std::cout << "row\n";
		for (auto elem: rows) {
			std::cout << "col\n";
			std::cout << elem <<"\n";
		}
	}	
	


}
