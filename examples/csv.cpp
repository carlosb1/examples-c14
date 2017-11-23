#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <iterator>
#include <numeric>
#include <functional>
#include "strtk.hpp"

namespace csv {
	class CSV {
		private:
			std::unordered_map<std::string, std::vector<std::string>> values;
		public:
			template<class T> void  addEntry(std::string key, T elem)  {
			   std::ostringstream stm;
			   stm << elem;
			   std::string value = stm.str();

			   std::vector<std::string> row;
			   if (this->values.find(key) !=this->values.end()) {
			   		row = this->values[key];
			   }

			   row.push_back(value);
			   this->values[key] = row;
			
			}

			inline std::string setUpRow(std::vector<std::string> & row) {
				if (row.empty()) {
					return std::string();
				}
				std::string res =  std::accumulate(std::next(row.begin()), row.end(),
						row[0],
						[](std::string a, std::string b) {
							return a+","+b;
						});
				return res;
			}
			inline void save(const std::string & filepath) {
				auto key_selector = [](auto pair) {
					return pair.first;
				};
				std::vector<std::string> keys(this->values.size());
				std::transform(values.begin(),values.end(),keys.begin(),key_selector);
				
				std::string head = setUpRow(keys);

				std::vector<std::vector<std::string>> values_to_save;
				for (auto key: keys) {
					int i = 0;
					for (auto new_value: this->values[key]) {
					 	if (((int)values_to_save.size())<= i) {
							values_to_save.resize(i+1);
						}
						values_to_save[i].push_back(new_value);
						i++;
					}
				}
			
		
				std::ofstream out(filepath);
				out << head <<"\n";
				for (auto row: values_to_save) {
					std::string str_row = setUpRow(row);
					out << str_row <<"\n";
				}
				out.close();

			}
			inline void load(const std::string & filepath) {
				strtk::token_grid::options options;
				options.column_delimiters = "| ,";
				options.support_dquotes = true;
				strtk::token_grid info_grid(filepath,options);
				
				/* header */
				strtk::token_grid::row_type head_row = info_grid.row(0);
				this->clear();
				
				std::vector<std::string> keys;
				for (std::size_t c = 0; c < head_row.size(); ++c) {
					keys.push_back(head_row.get<std::string>(c));
				}

		
				
				for (std::size_t r = 1; r < info_grid.row_count(); ++r) {
					strtk::token_grid::row_type row = info_grid.row(r);
					for (std::size_t c = 0; c < row.size(); ++c) {
						std::string id_key = keys[c];
						if(this->values.find(id_key) == this->values.end()) {
							this->values[id_key] = std::vector<std::string>();	
						}
						this->values[id_key].push_back(row.get<std::string>(c));
					}
				}

			}
			inline void clear() {
				this->values.clear();
			}
			inline std::unordered_map<std::string,std::vector<std::string>> get_map() {
				return this->values;
			}
	};

}

int main () {
	csv::CSV excel;
	excel.addEntry(std::string("key1"),"value10");
	excel.addEntry(std::string("key2"),"value11");
	excel.addEntry(std::string("key1"),"value20");
	excel.addEntry(std::string("key2"),"value21");
	excel.save(std::string("save.txt"));
	excel.clear();
	excel.load(std::string("save.txt"));
	std::unordered_map<std::string, std::vector<std::string>> content = excel.get_map();
	
	for (auto elem: content) {
		std::cout <<"key"<<elem.first<<"\n";
		for (auto value: elem.second) {
			std::cout << value << ","; 
		}
		std::cout <<"\n";
	}
}
