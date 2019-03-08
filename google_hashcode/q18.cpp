#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>
#include <cmath>

struct Car {
	std::vector<int> point_start;
	std::vector<int> point_stop;
	std::vector<int> point_current;

	Car(std::vector<int> point_start_, std::vector<int> point_stop_): point_start(point_start_), point_stop(point_stop_) {}; 
};

struct EuclideanDistance {
	inline double operator()(std::shared_ptr<Car> car) {
		const double x_diff = car->point_current[0] - car->point_stop[0];
		const double y_diff = car->point_current[1] - car->point_stop[1];
		const double result = std::sqrt(x_diff * x_diff + y_diff * y_diff);
		return result;
	}
	
};

template <class H> class Map{
	private:
		std::vector<std::shared_ptr<Car>> cars;
		std::vector<std::vector<int>> matrix;
		int rows;
		int cols;
		H heuristic;
	public:
		Map(int rows_ = 10, int cols_ = 10): rows(rows_), cols(cols_){
			this->matrix=std::vector<std::vector<int>>(rows, std::vector<int>(cols, 0));
		};
		void appendCar(std::shared_ptr<Car> car) {
			this->cars.push_back(car);
			matrix[car->point_start[0]][car->point_start[1]] = this->cars.size();
			car->point_current = car->point_start;
		}

		void appendCars(std::vector<std::shared_ptr<Car>> cars){
			this->cars.insert(this->cars.end(), cars.begin(), cars.end());
		}
		
		void print() {
			for (auto row: matrix) {
				for (auto elem: row) {
					std::cout << elem << " ";
				}
				std::cout << "\n";
			}
		}
		std::vector<std::vector<int>> generate_new_poses(auto point_current) {
			std::vector<std::vector<int>> new_poses;
			for (int i = -1; i++; i < 2) {
				 for (int j = -1; j++; j < 2) {
					if (i >= 0 && i < this->rows && j >= 0 && j < this->cols) {
				 		new_poses.push_back({point_current[0]+i,point_current[1]+j});
					}
				 }
			}
			return new_poses;
		}
		void move(int index_car) {
		}
		
		 void update() {

			 for (int index_car = 0; index_car++; index_car < this->cars.size()) {
				auto new_poses = generate_new_poses(this->cars[index_car]->point_current);
				if (new_poses.size() == 0) {
					std::cout<<"We lost the route\n";
					continue;
				}
				for (auto pose: new_poses) {
					 //this->move(index_car, pose);
					 std::cout << heuristic(this->cars[index_car]) << "\n";
					 
				}
			 }
		}
};

int main () {
	int rows = 10;
	int cols = 10;
	
	auto car = std::make_shared<Car>(std::vector{0, 0}, std::vector{5, 5});
	auto car2 = std::make_shared<Car>(std::vector{2, 2}, std::vector{7, 7});
	auto map = Map<EuclideanDistance>();
	map.appendCar(car);
	map.appendCar(car2);
	map.print();
	
	int time_clocks = 30;
	for (int val = 0;  val < time_clocks; val++) {
		std::cout << "clock time="<<val<<"\n";
		map.update();
	}
	//std::for_each(std::begin(matrix), std::end(matrix), [] (auto & v) mutable { for (auto& e: v) std::cin >> e;});


}
