#ifndef UTILS_PRIMES
#define UTILS_PRIMES
#include <cmath>
#include <vector>
namespace utils {
	bool primeNaive(int n) {
		if (n < 2) {
			return false;
		}
		for (int i = 2; i < n; i++) {
			if (n%i ==0) {
				return false;
			}
		}
		return true;
	}

	bool primeSlightlyBetter(int n) {
		if (n < 2) {
			return false;
		}
		int sqrt = (int)std::sqrt(n); 
		for (int i = 2; i <= sqrt; i++) {
			if (n%i ==0) return false;
		}
		return true;
	}

	void crossOff(std::vector<bool> & flags, int prime) {
		for (int i = prime*prime; i < (int)flags.size(); i+=prime) {
			flags[i] = false;
		}
	}
	int getNextPrime(std::vector<bool> & flags, int prime) {
		int next = prime + 1;
		while (next < (int)flags.size() && !flags[next]) {
			next++;
		}
		return next;
	}

	std::vector<bool> sieveOfEratosthenes(int max) {
		std::vector<bool> flags(max+1,0);
		//int count = 0;
		int prime = 2;
		while (prime <= std::sqrt(max)) {
			/* Cross off remaining multiples of prime */
			crossOff(flags,prime);
			/* Find next value which is true */
			prime = getNextPrime(flags,prime);
			if (prime >= (int)flags.size()) {
				break;
			}
		}

		return flags;
	}


	

}
#endif
