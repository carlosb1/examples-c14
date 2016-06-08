#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "naive_bayes_classifier.h"

TEST_CASE("Naive Bayers Classifier","[addRowCorrectly]") {
	ml::NaiveBayesClassifier classifier;
	std::string type("male");
	const float inputData = 5.855;
	ml::Sample sample = std::make_pair("height",inputData);
	classifier.addRow(type,sample);
	classifier.train();
	std::string param("height");
	ml::GaussianInfo info = classifier.getGaussianInfo(type,param);
	REQUIRE(info.mean == inputData);
	REQUIRE(info.values[0] == inputData);
	REQUIRE(info.variance ==  inputData);
		
	//TODO add test for this
	//TODO separate tests for this
	//TODO Change constructor for sample
//	ml::Sample sampleToPredict = std::make_pair("height",6.0);
	//TODO Parametri type
//	std::string type = classifier.predict(sampleToPredict);
	
};

