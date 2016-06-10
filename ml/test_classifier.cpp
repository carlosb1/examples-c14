#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "naive_bayes_classifier.h"

TEST_CASE("Add row correctly","[naive_bayes_classifier]") {
	ml::NaiveBayesClassifier classifier;
	const float inputData = 1;
	ml::Sample sample = std::make_pair("height",inputData);
	classifier.addRow("male",sample);

	//TODO move this test
	classifier.train();
	ml::GaussianInfo info = classifier.getGaussianInfo("male","height");
	REQUIRE(info.mean == inputData);
	REQUIRE(info.values[0] == inputData);
	REQUIRE(info.variance ==  inputData);
};

ml::Sample createSample (std::string param, float value) {
	return std::make_pair(param,value);
}

TEST_CASE("Add two rows correctly","[naive_bayes_classifier]") {
	//TODO ADD SETUP
	ml::NaiveBayesClassifier classifier;

	ml::Sample sample = createSample("height",1);
	classifier.addRow("male",sample);
	
	ml::Sample sample2 = createSample("height",1.5);
	classifier.addRow("male",sample2);

	classifier.train();
	ml::GaussianInfo info = classifier.getGaussianInfo("male","height");
	
	REQUIRE(info.values.size() == 2);
	REQUIRE(info.mean == 1.25);
	REQUIRE(info.values[0] == 1);
	REQUIRE(info.values[1] == 1.5);
	REQUIRE(info.variance ==  0.25 );
};

