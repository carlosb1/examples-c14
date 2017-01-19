#include "inheritance.h"
#include "inheritance2.h"
int main () {
	Child1 child1;
	Child2 child2;

	child1.helloFather();
	child1.helloMother();
	child1.helloChild();
	
	child2.helloFather();
	child2.helloMother();
	child2.helloChild();
	Join* p1 = new Join();
	Der1* p2 = p1;
	Base* p3 = p1;
	p1->foo();
	p2->foo();
	p3->foo();
	p1->helloWorld();
}
