#ifndef NAIVE_BAYES_CLASSIFIER
#define NAIVE_BAYES_CLASSIFIER
#include <map>
#include <vector>
#include <string>
#include <numeric>
#include <algorithm>
#include <iostream>
#include <cmath>

namespace ml {
	
	struct GaussianInfo{
		double mean;
		double variance;
		std::vector<float> values;
		bool isNull;
		GaussianInfo(float value) {
			values.push_back(value);
			mean = value;
			variance = 0;
			isNull = false;
		}
		GaussianInfo() {
			isNull=true;
		}
	};

	typedef std::pair<std::string,float> Sample;
	typedef std::map<std::string,GaussianInfo> Row;
	typedef std::pair<std::string,double> PredictedResult; 

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

			inline bool notExistTypeGaussian(std::string type) {
				return (gaussianTable.find(type) == gaussianTable.end());
			
			};
			inline double getProbability(double mean, double variance, double element ) {
				double multipl = 1.0/std::sqrt(2.0*variance*M_PI);
				double result =  multipl * std::exp(-std::pow(element - mean, 2.0) / (2.0*variance));
				return result;
			}



			inline void addRow(std::string type, Sample & param) {
				this->recollectedData.push_back(std::make_pair(type,param));
			};
			inline GaussianInfo getGaussianInfo(std::string type, std::string parameter) {
				/* Guards */
				if (notExistTypeGaussian(type)) {
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
					if (notExistTypeGaussian(key)) {
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

			inline bool notExistValue(std::map<std::string,GaussianInfo> & values, std::string name) {
				return values.find(name) == values.end();
			}
			inline bool isNotCalculable(GaussianInfo & gaussianInfo) {
				return (gaussianInfo.values.size()==1);
			}

			double calculateProbability (std::map<std::string,GaussianInfo> & values , std::vector<Sample> & samples, double probElem) {
					double accumulateProb = probElem;
					for (auto sample: samples) {
						std::string name = sample.first;
						/* Check if it exists */
						if (notExistValue(values,name)) {
							continue;
						}	
						float value = sample.second;
						GaussianInfo gaussianInfo = values[name];
						if (isNotCalculable(gaussianInfo)) {
							continue;
						}
						//TODO add test for this operation
						double probability = getProbability(gaussianInfo.mean,gaussianInfo.variance,value);
						accumulateProb*=probability;
					}
					return accumulateProb;
			}



			PredictedResult predict(std::vector<Sample> & samples) {
				double probElem = 1.0 / (double)this->gaussianTable.size();
				PredictedResult predictedResult;
				predictedResult.second = 0;
				for (const auto &pairValues: this->gaussianTable) {
					double accumulateProb = probElem;
					std::string key = pairValues.first;
					std::map<std::string,GaussianInfo> values = pairValues.second;
					//TODO test one type without samples
					//analyse sample
					accumulateProb = calculateProbability(values,samples,probElem);

					if (predictedResult.second < accumulateProb) {
						predictedResult.first= key;
						predictedResult.second = accumulateProb;
					}
				}

				return predictedResult;	
			}
				
		};
}
#endif 
