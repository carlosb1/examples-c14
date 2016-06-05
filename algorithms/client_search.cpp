#include <iostream>
#include "search.h"


int main () {
	const int size = 13;
 	int values [] ={4 ,5 ,6 ,7 ,2 ,3 ,65 ,12 ,88 ,12 ,38 ,1 ,8 };
	int temp[size];
	search::mergesort(values,temp,0,size-1);
	for (auto value: temp) {
		std::cout << value << ",";
	}
	std::cout << '\n';
}
