#define CPPHTTPLIB_OPENSSL_SUPPORT
#include <iostream>
#include "httplib.h"
int main () {
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
