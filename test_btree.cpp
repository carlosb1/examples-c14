#include <iostream>
#include "btree.h"
#include <vector>
#include <cstdlib>
#include <algorithm>
#include <string>
#include <ctime>

int main () {
	std::vector<int> inputVector(20);
	collections::BTree<int> tree = collections::BTree<int>();
	std::srand(std::time(0)); 

	std::for_each(inputVector.begin(), inputVector.end(), [](int &n){ n = (int) std::rand() % 100; });
//	std::for_each(inputVector.begin(), inputVector.end(), [](int &n){ std::cout<<"value="<<n<<std::endl; });

	for (int index=0; index< (int)inputVector.size() ; index++) {
		std::cout << "Insert new node: "<<inputVector[index]<<std::endl;
		tree = tree.insert(inputVector[index]);
	}
	tree.print();

	

}
