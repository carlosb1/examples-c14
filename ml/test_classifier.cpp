#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "naive_bayes_classifier.h"

TEST_CASE("Naives Bayers Classifier","[naive_bayes_classifier]") {
	ml::NaiveBayesClassifier classifier;
	REQUIRE(classifier.train()==true);
}

