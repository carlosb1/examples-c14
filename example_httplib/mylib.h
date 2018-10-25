#ifndef _MY_LIB_H_
#define _MY_LIB_H_
#include <string>

class ProdcastClient {
	public:
		ProdcastClient() {};
		void hello();
		void post();
	private:
		std::string hello_world{"hello"};
};

#endif

