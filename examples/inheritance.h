#include <iostream>

class Grandfather 
{	private:
	 int value;

	public:
	Grandfather(): value(0) {
		std::cout << "Creating default grand" << std::endl;
	};
	Grandfather(int value_): value(value_) {
		std::cout << "Creating non ndefault grand" << std::endl;
	};
	~Grandfather() {
		std::cout << "Killed Grandfather" << std::endl;
	}


};
class Father : virtual public Grandfather
{
	private:
	 	int value;
	public:
		Father(int value_): value(value_) {
			std::cout << "Creating father" << std::endl;
		};
		void helloFather() {
			std::cout << "Hello father: "<<value << std::endl;
		}
		virtual void helloBase() {
			std::cout << "Hello base: "<<value << std::endl;
		}
		virtual void helloChild () = 0;

		~Father() {
			std::cout << "Killed Father" << std::endl;
		}
};

class Mother: virtual public Grandfather {
	private:
		int value;
	public:
		Mother(int value_): value(value_) {
			std::cout << "Creating mother" << std::endl;
		};
	
		void helloMother() {
			std::cout << "Hello Mother: "<<value << std::endl;
		}
		~Mother() {
			std::cout << "Killed mother" << std::endl;
		}
};
class Child1: virtual public Father, virtual public Mother{
	private:
		int value;
	public:
		Child1():Father(1), Mother(2), value(121) {};
		void helloChild () {
			std::cout << "Hello Child: "<<value << std::endl;
		}
		~Child1() {
			std::cout << "Killed child1" << std::endl;
		}

};


class Child2: virtual public Father, virtual public Mother{
	private:
		int value;
	public:
		Child2():Father(1), Mother(2), value(122) {};
		void helloChild () {
			std::cout << "Hello Child: "<<value << std::endl;
		}
		
		~Child2() {
			std::cout << "Killed child2" << std::endl;
		}
};
