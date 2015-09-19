#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

int main()
{
	int inputNumber = 1213;
	std::string strNumber = std::to_string(inputNumber);
	std::sort(std::begin(strNumber), std::end(strNumber));
	std::vector<std::string> getValues;

	while (std::next_permutation(std::begin(strNumber), std::end(strNumber)))
	{
		if(std::find(getValues.begin(), getValues.end(),strNumber) == getValues.end()) {
			getValues.push_back(strNumber);
		}
	}
	std::cout << getValues.size()+1 << std::endl;

}
