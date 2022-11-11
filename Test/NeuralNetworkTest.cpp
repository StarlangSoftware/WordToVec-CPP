//
// Created by Olcay Taner YILDIZ on 28.12.2020.
//

#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include <Corpus.h>
#include "Dictionary/VectorizedDictionary.h"
#include "catch.hpp"
#include "../src/WordToVecParameter.h"
#include "../src/NeuralNetwork.h"


TEST_CASE("NeuralNetworkTest-testTrainEnglishCBow") {
    auto* english = new CorpusStream("english-similarity-dataset.txt");
    WordToVecParameter parameter = WordToVecParameter();
    parameter.setCbow(true);
    NeuralNetwork neuralNetwork = NeuralNetwork(english, parameter);
    VectorizedDictionary dictionary = neuralNetwork.train();
}

TEST_CASE("NeuralNetworkTest-testTrainEnglishSkipGram") {
    auto* english = new CorpusStream("english-similarity-dataset.txt");
    WordToVecParameter parameter = WordToVecParameter();
    parameter.setCbow(false);
    NeuralNetwork neuralNetwork = NeuralNetwork(english, parameter);
    VectorizedDictionary dictionary = neuralNetwork.train();
}

TEST_CASE("NeuralNetworkTest-testTrainTurkishCBow") {
    auto* turkish = new CorpusStream("turkish-similarity-dataset.txt");
    WordToVecParameter parameter = WordToVecParameter();
    parameter.setCbow(true);
    NeuralNetwork neuralNetwork = NeuralNetwork(turkish, parameter);
    VectorizedDictionary dictionary = neuralNetwork.train();
}

TEST_CASE("NeuralNetworkTest-testTrainTurkishSkipGram") {
    auto* turkish = new CorpusStream("turkish-similarity-dataset.txt");
    WordToVecParameter parameter = WordToVecParameter();
    parameter.setCbow(false);
    NeuralNetwork neuralNetwork = NeuralNetwork(turkish, parameter);
    VectorizedDictionary dictionary = neuralNetwork.train();
}