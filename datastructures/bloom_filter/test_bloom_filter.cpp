#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "bloom_filter.h"



TEST_CASE("should check exists","{bloom_filter}") {

	SECTION("Add a array with not contains") {
		uint64_t size = 100;
		uint8_t num_hashes = 100;
		BloomFilter bloomFilter(size,num_hashes);
		
		std::vector<uint8_t> test2 = {5,6,7,8};
		std::vector<uint8_t> test1 = {1,2,3,4};
		bloomFilter.add(&test1[0],test1.size());
		REQUIRE(bloomFilter.possiblyContains(&test2[0],test2.size())==false);
	}

	SECTION("Add a array with contains") {
		uint64_t size = 100;
		uint8_t num_hashes = 100;
		BloomFilter bloomFilter(size,num_hashes);
		
		std::vector<uint8_t> test1 = {1,2,3,4};
		bloomFilter.add(&test1[0],test1.size());
		REQUIRE(bloomFilter.possiblyContains(&test1[0],test1.size())==true);
	}
}
