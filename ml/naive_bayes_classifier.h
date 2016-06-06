#ifndef NAIVE_BAYES_CLASSIFIER
#define NAIVE_BAYES_CLASSIFIER
#include <map>
namespace ml {
	

	typedef std::map<std::string,float> Sample;
	struct GaussianValue{	
		double mean;
		double variance;
	}
	
	class NaiveBayesClassifier {
		inline void addRow(std::string & key, Sample &values ) {
			this->table.insert(std::pair<std::string,Sample>(key,values));
		};
		private:
			std::multimap<std::string,Sample> table;

		public:
			void train () {
				for (auto row: table) {
					std::string key = row.first;
					Sample values = row.second;
				}

			}
			void classify (Sample & sample) {
			}	

	};
};
#endif 
