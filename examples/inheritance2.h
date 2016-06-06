#include <iostream>
class Base {
	public:
		virtual void foo() = 0;
		virtual void bar() = 0;
};
class Der1 : public virtual Base {
	public:
		virtual void foo();
};
void Der1::foo()
{ bar(); }
class Der2 : public virtual Base {
	public:
		//virtual void bar();
		virtual void bar () {
		   	std::cout << "I am a bar!!" << std::endl;
		   }
};
class Join : public Der1, public Der2 {
	        public:
		   void helloWorld() {
			std::cout << "Hello world" << std::endl;	
		  };
};
