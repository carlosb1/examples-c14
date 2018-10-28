#include "S3_wrap.h"
#include "S3.h"

#ifdef __cplusplus
	extern "C" {
#endif 
	
	void hello_world() {
		std::cout << "hello world\n";
	}

	void hello(const char *example_text) {
		std::string tex(example_text);	
		std::cout << "Hello "<<tex << "\n";
	}


#ifdef __cplusplus
	}
#endif

