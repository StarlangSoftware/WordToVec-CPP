//
// Created by Olcay Taner YILDIZ on 28.12.2020.
//

#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include <Corpus.h>
#include <VectorizedDictionary.h>
#include "catch.hpp"
#include "../WordToVecParameter.h"
#include "../NeuralNetwork.h"

VectorizedDictionary train(Corpus& corpus, bool cBow){
    WordToVecParameter parameter = WordToVecParameter();
    parameter.setCbow(cBow);
    NeuralNetwork neuralNetwork = NeuralNetwork(corpus, parameter);
    return neuralNetwork.train();
}

TEST_CASE("NeuralNetworkTest-testTrainEnglishCBow") {
    Corpus english = Corpus("english-similarity-dataset.txt");
    VectorizedDictionary dictionary = train(english, true);
}

TEST_CASE("NeuralNetworkTest-testTrainEnglishSkipGram") {
    Corpus english = Corpus("english-similarity-dataset.txt");
    VectorizedDictionary dictionary = train(english, false);
}

TEST_CASE("NeuralNetworkTest-testTrainTurkishCBow") {
    Corpus turkish = Corpus("turkish-similarity-dataset.txt");
    VectorizedDictionary dictionary = train(turkish, true);
}

TEST_CASE("NeuralNetworkTest-testTrainTurkishSkipGram") {
    Corpus turkish = Corpus("turkish-similarity-dataset.txt");
    VectorizedDictionary dictionary = train(turkish, false);
}