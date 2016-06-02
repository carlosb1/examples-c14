#include "inheritance.h"
int main () {
	Child1 child1;
	Child2 child2;

	child1.helloFather();
	child1.helloMother();
	child1.helloChild();
	
	child2.helloFather();
	child2.helloMother();
	child2.helloChild();
}
