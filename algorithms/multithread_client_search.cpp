#include <iostream>
#include "multithread_search.h"
#include "search.h"
#include <ctime>
#include "benchmark/benchmark_api.h"

void generate_random_array  (int output [], int size, int range) {
	std::srand((unsigned)time(NULL));
	for (int i = 0; i < size; i++) {
		output[i]= 1 + rand() % range;
	}
}

static void BM_mergesort_multithread(benchmark::State &state) {
	const int size = 100;
	int values[size];
	int temp[size];
	while (state.KeepRunning() ) {
		generate_random_array(values,size,100);
		search_multithread::mergesort(values,temp,0,size-1);
	}
}

static void BM_mergesort(benchmark::State &state) {
	const int size = 100;
	int values[size];
	int temp[size];
	while (state.KeepRunning() ) {
		generate_random_array(values,size,100);
		search::mergesort(values,temp,0,size-1);
	}
}

BENCHMARK(BM_mergesort_multithread);

BENCHMARK(BM_mergesort);
BENCHMARK_MAIN();
/*
int main () {
	const int size = 13;
 	int values [] ={4 ,5 ,6 ,7 ,2 ,3 ,65 ,12 ,88 ,12 ,38 ,1 ,8 };
	int temp[size];
	search::mergesort(values,temp,0,size-1);
	for (auto value: temp) {
		std::cout << value << ",";
	}
	std::cout << '\n';
}
*/
