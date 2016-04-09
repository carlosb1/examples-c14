#include <iostream>  // includes cin to read from stdin and cout to write to stdout
#include <vector>
#include <algorithm>
#include <sstream>
#include <cmath>
using namespace std;  // since cin and cout are both in namespace std, this saves some text

std::vector<int> num_to_digits (int num) {
	std::vector<int> digits;
	do {
		int digit = num % 10;
		digits.push_back(digit);
		num /= 10;
	} while (num > 0);
	return digits;

}

bool contains_value(std::vector<int> accumulate_values, int possible_value) {
	return std::find(accumulate_values.begin(),accumulate_values.end(), possible_value)!=accumulate_values.end();
}

/*
template <typename T> std::string vector_to_string (std::vector<T> v)  {
	std::stringstream ss;
	for(size_t i = 0; i < v.size(); ++i)
	{
		  if(i != 0)
			      ss << ",";
		    ss << v[i];
	}
	std::string s = ss.str();
	return s;
}
*/

int TOTAL_POSSIBLE_VALUES_DIFS = 10;
int counting_sheep (int input_value) {
	bool finish = false;
	int mult = 1;
	std::vector<int> accumulate_values;
	int mult_value = -1;
	while (!finish) {
		mult_value = mult * input_value;
		std::vector<int> values = num_to_digits(mult_value);
		std::vector<int> values_to_add;
		for (auto possible_value: values) {
			if  (!contains_value(accumulate_values,possible_value) && !contains_value(values_to_add,possible_value)) {
				values_to_add.push_back(possible_value);
			}
		}
		accumulate_values.insert(accumulate_values.end(),values_to_add.begin(),values_to_add.end());
	//	std::cout << vector_to_string(accumulate_values) << std::endl;
		values_to_add.clear();
		
		finish = ((int)accumulate_values.size() == TOTAL_POSSIBLE_VALUES_DIFS);
		mult++;
		
	}

	return mult_value;	
}



long int LIMIT_N = std::pow(10,6);
int LIMIT_T = 100;
int main() {
	int t, n, m;
	cin >> t;  // read t. cin knows that t is an int, so it reads it as such.
	if (t > LIMIT_T) {
		return 0;
	}


	for (int i = 1; i <= t; ++i) {
		cin >> n;
		if (n > LIMIT_N) {
			continue;
		}

		if (n == 0) {
			cout << "Case #" << i << ": " << "INSOMNIA" << endl;
			continue;
		}
	
		m = counting_sheep(n);
		cout << "Case #" << i << ": " << m << endl;

	}
	return 0;
}
