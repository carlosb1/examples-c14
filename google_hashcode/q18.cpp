#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>

struct Car {
	int point_start;
	int point_stop;

	Car(int point_start_, int point_stop_): point_start(point_start_), point_stop(point_stop_) {}; 
	static std::shared_ptr<Car> newCar(int point_start_, int point_stop_) {
		return std::make_shared<Car>(point_start_, point_stop_);
	}
};


void print_matrix(std::vector<std::vector<int>> & matrix) {
	for (auto row: matrix) {
		for (auto elem: row) {
			std::cout << elem;
		}
		std::cout << "\n";
	}

}
int main () {
	int rows = 4;
	int cols = 4;
	
	std::vector<std::vector<int>> matrix(rows, std::vector<int>(cols, 0));
	
	auto car = Car::newCar(1,1);	

	//std::for_each(std::begin(matrix), std::end(matrix), [] (auto & v) mutable { for (auto& e: v) std::cin >> e;});


}
