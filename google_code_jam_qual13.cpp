#include <vector>
#include <cmath>
#include <iostream>  // includes cin to read from stdin and cout to write to stdout
using namespace std;  // since cin and cout are both in namespace std, this saves some text


int change_base(int value, int base) {
	std::vector<int> mults;
	while (value >=base) {
		int rest = value % base;
		value = ((value-rest) / base);
		mults.push_back(rest);
	}
	int acum_value=0;
	for (int index = mults.size(); index >=0; index--) {
		int mult = mults[index];
		acum_value+=mult*pow(base,index);
	}

	return acum_value;
	
}
bool is_prime(int num) {
	int count = 0;
	for(int i=2;i<=num/2;i++){
	     if(num%i==0){
		count++;
		break;
	     }
        }
        return(count==0 && num!= 1);

}



int main() {
	int t, n, j;
	cin >> t;  // read t. cin knows that t is an int, so it reads it as such.
	cin >> n;
	cin >> j;

	
	unsigned int shift_count = 0;
	unsigned int value = (unsigned int)33;
	
		cout << "Case #" << n; 

		int number_of_found= 0;
		std::vector<int> number_values;
		while (number_of_found== j) {
			

			/* find */
			for (int base = 2; base < 11; base++) {
				int new_value_base = change_base(value,base);
				if  (is_prime(new_value_base)) {
					break;					
				}
				number_values.push_back(new_value_base);
			}
			if (number_values.size() == 9) {
				//PRINT IN BINARY
				//cout <<  value;
				for (int i = 0; i< (int) number_values.size(); i++){
					cout <<" "<<number_values[i];	
				}
				cout << '\n';
			}
					
			number_values.clear();
				
			/* next correct binary to analyse*/	
			value=value | (++shift_count << 1);	
		}

	
	/*
	for (int i = 1; i <= t; ++i) {
		cin >> n >> m;  // read n and then m.
		cout << "Case #" << i << ": " << (n + m) << " " << (n * m) << endl;
	}
*/
	return 0;
}
