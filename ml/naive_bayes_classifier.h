#ifndef NAIVE_BAYES_CLASSIFIER
#define NAIVE_BAYES_CLASSIFIER
#include <map>
#include <vector>
#include <string>

namespace ml {
	
	typedef std::pair<std::string,float> Sample;

	struct GaussianInfo{
		double mean;
		double variance;
		std::vector<float> values;
		
	};
	typedef std::map<std::string,GaussianInfo> Row;
	class NaiveBayesClassifier {

		private:
			std::vector<std::pair<std::string,Sample>> recollectedData; 
			std::map<std::string,std::map<std::string,GaussianInfo>> gaussianTable; 
		public:		
			inline void addRow(std::string & type, Sample & param) {
				this->recollectedData.push_back(std::make_pair(type,param));
			};
			inline GaussianInfo getGaussianInfo(std::string & type, std::string & parameter) {
				//TODO add checker
				return gaussianTable[type][parameter];

			}
			//TODO add clean method
			void train () {
				for (auto data: this->recollectedData) {
					std::string key = data.first;
					Sample sample = data.second;
				
					//TODO set up a correct constructor
					Row row;
					GaussianInfo gaussianInfo;
					gaussianInfo.values.push_back(sample.second);
					gaussianInfo.mean = sample.second;
					gaussianInfo.variance = sample.second;
					row[sample.first]= gaussianInfo;
					this->gaussianTable[key]=row;
				}

			}
			std::string predict(Sample & sample) {
				return std::string();	
			}
				
		};
}
#endif 
