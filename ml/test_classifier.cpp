#define CATCH_CONFIG_MAIN
#include "vector"
#include "catch.hpp"
#include "naive_bayes_classifier.h"

ml::Sample createSample (std::string param, float value) {
	return std::make_pair(param,value);
}
void insertSamples(ml::NaiveBayesClassifier & classifier,std::string type,  std::string param, std::vector<float> values) {
	for (auto value: values) {
		ml::Sample sample = createSample(param,value);
		classifier.addRow(type,sample);
	}
}

TEST_CASE("testing add information","[naive_bayes_classifier]") {
	ml::NaiveBayesClassifier classifier;

	SECTION("Add row correctly") {
	std::vector<float> v {1.};
		insertSamples(classifier,"male","height",v);	
		
		//TODO isolate testing
		classifier.train();
		ml::GaussianInfo info = classifier.getGaussianInfo("male","height");
		REQUIRE(info.mean == 1.);
		REQUIRE(info.values[0] == 1.);
		REQUIRE(info.variance ==  0.);
	};
	SECTION("Add two rows correctly") {
		std::vector<float> v {1., 1.5};
		insertSamples(classifier,"male","height",v);	
		
		classifier.train();
		ml::GaussianInfo info = classifier.getGaussianInfo("male","height");	
		REQUIRE(info.values.size() == 2);
		REQUIRE(info.mean == 1.25);
		REQUIRE(info.values[0] == 1);
		REQUIRE(info.values[1] == 1.5);
		REQUIRE(info.variance ==  0.25 );	
	};

	SECTION("Add different type of samples for testing test") {
		std::vector<float> v {1., 1.5};
		insertSamples(classifier,"male","height",v);	
		std::vector<float> v2 {1.};
		insertSamples(classifier,"male","weight",v2);	
	
		classifier.train();
		ml::GaussianInfo info = classifier.getGaussianInfo("male","weight");
		
		REQUIRE(info.values.size() == 1);
		REQUIRE(info.values[0] == 1);
		REQUIRE(info.variance ==  0 );
		REQUIRE(info.mean ==  1 );
	};

	
	SECTION("It doesn't exist the sample") {
		classifier.train();
		ml::GaussianInfo info = classifier.getGaussianInfo("male","weight");
		REQUIRE(info.values.size() == 0);
	};
	
	SECTION("Add multiple types for testing with a sample ") {
		std::vector<float> v {1};
		insertSamples(classifier,"male","height",v);	
		std::vector<float> v2 {2};
		insertSamples(classifier,"woman","height",v2);	
	
		classifier.train();
		
		ml::GaussianInfo info = classifier.getGaussianInfo("male","height");	
		REQUIRE(info.values.size() == 1);
		
		REQUIRE(info.values[0] == 1);

		ml::GaussianInfo info2 = classifier.getGaussianInfo("woman","height");	
		REQUIRE(info2.values.size() == 1);
		REQUIRE(info2.values[0] == 2);
	};

	SECTION("Test simple prediction") {
		std::vector<float> v {1};
		insertSamples(classifier,"male","height",v);	
	
		classifier.train();

		ml::Sample sample = createSample("height",1.0);
		std::vector<ml::Sample> valuesPredicts{sample};
		ml::PredictedResult predictedValue =  classifier.predict(valuesPredicts);
		
		REQUIRE(predictedValue.first == "male");
	};

	SECTION("Test prediction two values but without variance") {
		std::vector<float> v {4};
		insertSamples(classifier,"male","height",v);	
		std::vector<float> v2 {2};
		insertSamples(classifier,"woman","height",v2);	
		
		classifier.train();

		ml::Sample sample = createSample("height",2.0);
		std::vector<ml::Sample> valuesPredicts{sample};
		ml::PredictedResult predictedValue =  classifier.predict(valuesPredicts);
		
		REQUIRE(predictedValue.first == "male");
		REQUIRE(predictedValue.second == 0.5);
	};	
	SECTION("Test prediction two values but with variance") {
		std::vector<float> v {4,5};
		insertSamples(classifier,"male","height",v);	
		std::vector<float> v2 {1,2};
		insertSamples(classifier,"woman","height",v2);	
		
		classifier.train();

		ml::Sample sample = createSample("height",2.0);
		std::vector<ml::Sample> valuesPredicts{sample};
		ml::PredictedResult predictedValue =  classifier.predict(valuesPredicts);
		
		REQUIRE(predictedValue.first == "woman");
	};
};




