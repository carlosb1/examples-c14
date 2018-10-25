#define CPPHTTPLIB_OPENSSL_SUPPORT
#include "mylib.h"
#include "httplib.h"
#include <iostream>


void ProdcastClient::hello() {
	std::cout << this->hello_world << "\n";
}

void ProdcastClient::post () {

	httplib::SSLClient cli("digg.com", 443);
	//httplib::Client cli("google.com", 80);
	auto res = cli.Get("/");
	if (res && res->status == 200) {
		std::cout << res->body << std::endl;
	} else {
		std::cout << "It is not working\n";
		std::cout << res->body << std::endl ;
		//std::cout  << res->status << std::endl;
	}
}

extern "C" void apply_hello(){
	ProdcastClient c;
	c.hello();
}
extern "C" void apply_post() {
	ProdcastClient c;
	c.post();
}
