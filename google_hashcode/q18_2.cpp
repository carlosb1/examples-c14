#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>
#include <cmath>
#include <utility>


struct Car {
	std::vector<int> point_start;
	std::vector<int> point_stop;
	std::vector<int> point_current;
	Car(std::vector<int> point_start_, std::vector<int> point_stop_): point_start(point_start_), point_stop(point_stop_), point_current(point_start_) {}; 
};
bool operator == (Car const& a, Car const & b) {
	return (a.point_start == b.point_start && a.point_stop == b.point_stop && a.point_current == b.point_current);
}

bool operator != (Car const& a, Car const & b) {
	return (a.point_start != b.point_start || a.point_stop != b.point_stop || a.point_current == b.point_current);
}


struct Map {
	std::vector<Car> cars;
//	std::vector<std::vector<int>> matrix;
};

bool operator == (Map const& a, Map const & b) {
	if (a.cars.size() != a.cars.size()) {
		return false;
	}
	for (int ind = 0; ind < a.cars.size(); ind++) {
		if (a.cars[ind] != b.cars[ind]) {
			return false;
		}
	}
	return true;
}

double distance(auto current_pos, auto new_pos) {
	const double x_diff = current_pos[0] - new_pos[0];
	const double y_diff = current_pos[1] - new_pos[1];
	const double result = std::sqrt(x_diff * x_diff + y_diff * y_diff);
	return result;
}
	
double calculate_heuristic(Map & map) {
	double h = 0.;
	for (auto car: map.cars) {
		h += distance(car.point_current, car.point_stop);
	}
	return h;
}

std::vector<std::vector<int>> generate_new_poses(auto point_current) {
	std::vector<std::vector<int>> new_poses;
	for (int i = -1; i < 2; i++) {
		for (int j = -1; j++; j < 2) {
			if ((point_current[0] + i) >= 0 && (point_current[0] + i)  < this->rows && (point_current[1] + j)  >= 0 && (point_current[1] + j)  < this->cols) {
				if ( i==0 && j==0) {
					continue;
				}
				new_poses.push_back({point_current[0]+i,point_current[1]+j});
			}
		}
	}
	return new_poses;
}

std::vector<Map> generate_new_maps(Map & map) {
	for (auto car: map.cars) {
		
	}
	

	//add new combinations but we avoid repeat
}


int main() {
	std::vector<Map> maps;
	auto car = Car(std::vector{0, 0}, std::vector{5, 5});
	auto car2 = Car(std::vector{2, 2}, std::vector{7, 7});
	auto init_case = {car, car2};
	std::cout << "hi my friend\n";	
	auto map = Map{init_case};
	std::cout << "heuristic: "<< calculate_heuristic(map) << "\n";
	maps.push_back(map);	
}


