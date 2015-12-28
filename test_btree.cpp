#include <iostream>
#include "btree.h"
#include <vector>
#include <cstdlib>

void  CreateRandomVector (std::vector<int> vectToModify) {
	for (int index=0; index<(int)vectToModify.size(); index++) {
		vectToModify[index] = (int) std::rand() % 100;
	}

}

int main () {
	std::vector<int> inputVector(20);
	CreateRandomVector(inputVector);
	collections::BTree<int> tree = collections::BTree<int>();
	
	for (int index=0; index< (int)inputVector.size() ; index++) {
		tree.insert(inputVector[index]);
	}

}
