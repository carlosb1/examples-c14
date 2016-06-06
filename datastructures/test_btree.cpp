#include <iostream>
#include "btree.h"
#include <vector>
#include <cstdlib>
#include <algorithm>
#include <string>
#include <ctime>
#include "rb_tree.h"

int main () {
	std::vector<int> inputVector {69,41,68,51,41,11,73,32,7,45,74,60,82,84,93,33,47,70,58,18};
	collections::BTree<int> tree = collections::BTree<int>();

	for (int index=0; index< (int)inputVector.size() ; index++) {
		tree = tree.insert(inputVector[index]);
	}
	tree.print();
	bool balanced = tree.isBalance();
	std::cout << "balanced tree="<<balanced<<std::endl;

	RBTree<int> rbTree = RBTree<int>();
	
	for (int index=0; index< (int)inputVector.size() ; index++) {
		rbTree = rbTree.inserted(inputVector[index]);
	}
	


}
