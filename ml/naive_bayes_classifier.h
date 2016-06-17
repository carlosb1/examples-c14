#ifndef NAIVE_BAYES_CLASSIFIER
#define NAIVE_BAYES_CLASSIFIER
#include <map>
#include <vector>
#include <string>
#include <numeric>
#include <algorithm>
#include <iostream>

namespace ml {
	
	typedef std::pair<std::string,float> Sample;

	struct GaussianInfo{
		double mean;
		double variance;
		std::vector<float> values;
		bool isNull;
		GaussianInfo(float value) {
			values.push_back(value);
			mean = value;
			variance = value;
			isNull = false;

		}
		

		
		GaussianInfo() {
			isNull=true;
		}
		
	};
	typedef std::map<std::string,GaussianInfo> Row;

	/**
	 * Implements mean function
	 * @param values vector of values
	 * */
	inline double mean(std::vector<float> values) {
		double sum = std::accumulate(values.begin(), values.end(), 0.0);
		return sum / values.size();
	}


	/**
	 * Calculates variance value from a set of number and their mean
	 * @param mean mean of numbers
	 * @param set of values to get variance
	 * */
	inline double variance (double mean, std::vector<float> values) {
		std::vector<double> diff(values.size());
		std::transform(values.begin(), values.end(), diff.begin(), [mean](double x) { return x - mean; });
		double sq_sum = std::inner_product(diff.begin(), diff.end(), diff.begin(), 0.0);
		return std::sqrt(sq_sum / values.size());
	}

	class NaiveBayesClassifier {

		private:
			std::vector<std::pair<std::string,Sample>> recollectedData; 
			std::map<std::string,std::map<std::string,GaussianInfo>> gaussianTable; 
		public:		

			inline bool existTypeGaussian(std::string type) {
				return (gaussianTable.find(type) == gaussianTable.end());
			
			};


			inline void addRow(std::string type, Sample & param) {
				this->recollectedData.push_back(std::make_pair(type,param));
			};
			inline GaussianInfo getGaussianInfo(std::string type, std::string parameter) {
				/* Guards */
				if (existTypeGaussian(type)) {
					return GaussianInfo();
				}


				std::map<std::string,GaussianInfo> info = gaussianTable[type];
				if (info.find(parameter) == info.end()) {
					return GaussianInfo();
				}

				return gaussianTable[type][parameter];

			}
			void train () {
				for (auto data: this->recollectedData) {
					std::string key = data.first;
					Sample sample = data.second;
				
					Row row;
					GaussianInfo gaussianInfo;
					if (existTypeGaussian(key)) {
						gaussianInfo = GaussianInfo(sample.second);
					}
					else {
						row = this->gaussianTable[key];
						gaussianInfo = row[sample.first];
						gaussianInfo.values.push_back(sample.second);
						//TODO it is calculating all the time the mean and the variance...
						//TODO it can be improved
						gaussianInfo.mean  = ml::mean(gaussianInfo.values);
						gaussianInfo.variance = ml::variance(gaussianInfo.mean,gaussianInfo.values);

					}
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
