#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "naive_bayes_classifier.h"

TEST_CASE("Add row correctly","[naive_bayes_classifier]") {
	ml::NaiveBayesClassifier classifier;
	std::string type("male");
	const float inputData = 1;
	ml::Sample sample = std::make_pair("height",inputData);
	classifier.addRow(type,sample);
	classifier.train();
	std::string param("height");
	ml::GaussianInfo info = classifier.getGaussianInfo(type,param);
	REQUIRE(info.mean == inputData);
	REQUIRE(info.values[0] == inputData);
	REQUIRE(info.variance ==  inputData);
};

TEST_CASE("Add two rows correctly","[naive_bayes_classifier]") {
	//TODO ADD SETUP
	ml::NaiveBayesClassifier classifier;

	//TODO Function to create elements
	std::string type("male");
	const float inputData = 1;
	ml::Sample sample = std::make_pair("height",inputData);
	classifier.addRow(type,sample);
	
	std::string type2("male");
	const float inputData2 = 2;
	ml::Sample sample2 = std::make_pair("height",inputData2);
	classifier.addRow(type2,sample2);

	classifier.train();
	std::string param("height");
	ml::GaussianInfo info = classifier.getGaussianInfo(type,param);
	REQUIRE(info.values.size() == 2);
	REQUIRE(info.values[0] == 1);
	REQUIRE(info.values[1] == 1.5);
	REQUIRE(info.mean == 1.5);
	REQUIRE(info.variance ==  (1.25 / 2.0) );
};

