#ifndef NAIVE_BAYES_CLASSIFIER
#define NAIVE_BAYES_CLASSIFIER
#include <map>
namespace ml {
	

	typedef std::map<std::string,float> Sample;
	struct GaussianValue{
		double mean;
		double variance;
	};
	
	class NaiveBayesClassifier {
		inline void addRow(std::string & key, Sample &values ) {
			this->table.insert(std::pair<std::string,Sample>(key,values));
		};
		private:
			std::multimap<std::string,Sample> table;
			std::map<std::string,std::map<std::string,GaussianValue>> gaussianTable; 
		public:
			void train () {
				std::map<std::string,std::map<std::string,GaussianValue>>::iterator it;
				for (auto row: table) {
					std::string key = row.first;
					Sample values = row.second;
					it = gaussianTable.find(key);
					if (it != gaussianTable.end()) {
						//exists
					} else {
						//no exists
						//Add values
						//gaussianTable[it->first]=;

					}
				}
			}
			void classify (Sample & sample) {

			}	
	};
};
#endif 
