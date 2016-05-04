#include <vector>
#include <cmath>
#include <string>
#include <iostream>  // includes cin to read from stdin and cout to write to stdout
using namespace std;  // since cin and cout are both in namespace std, this saves some text



int change_base(int value, int base) {
	int acum_value = 0;
	int index = 0;
	while (value > 0) {
		int rem = value & 1; 
		value = (value) / 2;
		acum_value+= rem * pow(base,index);
		index++;
	}

	return acum_value;
	
}
bool is_prime(int num, int & result) {
	int count = 0;
	for(int i=2;i<=num/2;i++){
	     if(num%i==0){
		count++;
	     	result = i;
		break;
	     } 
        }
        return(count==0 && num!= 1);

}

std::string dec_to_bin(unsigned number) {

	if (number == 0) { return "0"; }
	if (number == 1) { return "1";}
	if (number % 2 == 0) {
		return dec_to_bin(number / 2) + "0";
	} else {
		return dec_to_bin(number / 2) + "1";
	}	
}



int main() {
	int t, n, j;
	cin >> t;  // read t. cin knows that t is an int, so it reads it as such.
	cin >> n;
	cin >> j;

	
	unsigned int init_value = ((unsigned int)1<<(n-1))+1;
	cout << dec_to_bin(init_value) << '\n';
	cout << "Case #" << t<<":"<<'\n'; 

	int number_of_found= 0;
	std::vector<int> number_values;
	unsigned int loop_value = init_value;
	int count = 0;
	while (number_of_found!=j) {
		/* find */
		//cout << dec_to_bin(loop_value) << '\n';
		for (int base = 2; base < 11; base++) {
			int new_value_base = change_base(loop_value,base);
			int divisor = 0;
			if  (is_prime(new_value_base,divisor)) {
				break;					
			}
			number_values.push_back(divisor);
		}
		if (number_values.size() == 9) {
			number_of_found+=1;
			cout <<  dec_to_bin(loop_value) ;
			for (int i = 0; i< (int) number_values.size(); i++){
				cout <<" "<<number_values[i];	
			}
			cout << '\n';
		}
		number_values.clear();
				
		/* next correct binary to analyse*/	
		loop_value= (++count<<1) | init_value;
		//cout << dec_to_bin(loop_value) << '\n';
	}

	
	/*
	for (int i = 1; i <= t; ++i) {
		cin >> n >> m;  // read n and then m.
		cout << "Case #" << i << ": " << (n + m) << " " << (n * m) << endl;
	}
*/
	return 0;
}
