
#include <iostream>  
#include <vector>
#include <stack>
//#include <sstream>

using namespace std;  // since cin and cout are both in namespace std, this saves some text

/*template <typename T> std::string vector_to_string (std::vector<T> v)  {
	std::stringstream ss;
	for(size_t i = 0; i < v.size(); ++i)
	{
		  if(i != 0)
			      ss << ",";
		    ss << v[i];
	}
	std::string s = ss.str();
	return s;
}*/

bool is_solution(std::string & sequence) {
	for (int i = 0; i < (int) sequence.size(); i++) {
		if (sequence[i] == '-') {
			return false;
		}

	}
	return true;
}

std::string maneuver (std::string & sequence, int pivot) {
	std::stack<char> modified_values;
	for (int end_index=pivot; end_index >= 0; end_index--) {
		char value = sequence[end_index];
		value = (value=='+') ? '-' : '+';
		modified_values.push(value);	
	}
	/* build string */
	std::string result(sequence.size(),' ');

	/* set up modified values*/
	int size_stack = (int)modified_values.size();
	for (int index=0; index < size_stack; index++) {
		char value_to_add = modified_values.top();
		modified_values.pop();
		result[index]=value_to_add;	
	}
	/* set up no modified values */
	for (int index = pivot+1; index < (int)sequence.size(); index++) {
		result[index]=sequence[index];	
	}
	return result;
}


/*
void pancake_recursive(std::string sequence,int & min_movs, int current_movs, int current_index) {
	// is solution? 
	if (is_solution(sequence)) {
		if (min_movs == -1 || min_movs > current_movs) {
			min_movs = current_movs;
		}
		return;
	}
	//there are not more possibilites
	if (current_index >= (int)sequence.size()) {
		return;	
	}


	// if not solution, we iterate 
	for (int index = current_index; index < (int)sequence.size(); index++ ) {
		std::string new_sequence = maneuver(sequence,index);
		pancake_recursive(new_sequence,min_movs,current_movs+1,current_index+1);
	}

}
*/
struct stack_params {
	std::string sequence;
	int current_movs;
	int current_index;
};
	

int pancake_iterative(std::string sequence, int current_movs, int current_index) {
	int min_movs = -1;
	std::stack<stack_params> possible_results;
	stack_params params;
	params.sequence = sequence;
	params.current_movs = current_movs;
	params.current_index = current_index;
	possible_results.push(params);

	while (!possible_results.empty()) {
		stack_params params = possible_results.top();
		possible_results.pop();
		std::string sequence = params.sequence;
		int current_movs = params.current_movs;
		int current_index = params.current_index;	
		/* is solution? */
		if (is_solution(sequence)) {
			if (min_movs == -1 || min_movs > current_movs) {
				min_movs = current_movs;
			}
			continue;
		}
		//there are not more possibilites
		if (current_index >= (int)sequence.size()) {
			continue;	
		}

		/* if not solution, we iterate  */
		for (int index = current_index; index < (int)sequence.size(); index++ ) {
			std::string new_sequence = maneuver(sequence,index);
			stack_params new_params;
			new_params.sequence=new_sequence;
			new_params.current_movs = current_movs+1;
			new_params.current_index =current_index+1;
			possible_results.push(new_params);
		}
	}
	return min_movs;
}




int pancake (std::string sequence) {
	int current_movs = 0;
	int current_index = 0;
	int min_movs = pancake_iterative(sequence,current_movs,current_index);
	return min_movs;
}


int main() {
	int t;
	std::string sequence;
	cin >> t;  // read t. cin knows that t is an int, so it reads it as such.
	std::getline(cin,sequence);
	for (int i = 1; i <= t; ++i) {
		std::getline(cin,sequence);
		int result = pancake(sequence);		
		cout << "Case #" << i << ": " << result<< endl;
	}
	return 0;
}
