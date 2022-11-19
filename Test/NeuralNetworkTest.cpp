//
// Created by Olcay Taner YILDIZ on 28.12.2020.
//

#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include <Corpus.h>
#include "Dictionary/VectorizedDictionary.h"
#include "catch.hpp"
#include "../src/WordToVecParameter.h"
#include "../src/NeuralNetwork.h"
#include "../src/SemanticDataSet.h"


TEST_CASE("NeuralNetworkTest-testTrainEnglishCBow") {
    SemanticDataSet mc, rg, ws, av, men, mturk, rare;
    auto* english = new Corpus("english-xs.txt");
    mc = SemanticDataSet("MC.txt");
    rg = SemanticDataSet("RG.txt");
    ws = SemanticDataSet("WS353.txt");
    men = SemanticDataSet("MEN.txt");
    mturk = SemanticDataSet("MTurk771.txt");
    rare = SemanticDataSet("RareWords.txt");
    WordToVecParameter parameter = WordToVecParameter();
    parameter.setCbow(true);
    NeuralNetwork neuralNetwork = NeuralNetwork(english, parameter);
    cout << neuralNetwork.vocabularySize() << endl;
    VectorizedDictionary dictionary = neuralNetwork.train();
    SemanticDataSet mc2 = mc.calculateSimilarities(dictionary);
    cout << "(" << mc.size() << ") " << mc.spearmanCorrelation(mc2) << endl;
    SemanticDataSet rg2 = rg.calculateSimilarities(dictionary);
    cout << "(" << rg.size() << ") " << rg.spearmanCorrelation(rg2) << endl;
    SemanticDataSet ws2 = ws.calculateSimilarities(dictionary);
    cout << "(" << ws.size() << ") " << ws.spearmanCorrelation(ws2) << endl;
    SemanticDataSet men2 = men.calculateSimilarities(dictionary);
    cout << "(" << men.size() << ") " << men.spearmanCorrelation(men2) << endl;
    SemanticDataSet mturk2 = mturk.calculateSimilarities(dictionary);
    cout << "(" << mturk.size() << ") " << mturk.spearmanCorrelation(mturk2) << endl;
    SemanticDataSet rare2 = rare.calculateSimilarities(dictionary);
    cout << "(" << rare.size() << ") " << rare.spearmanCorrelation(rare2) << endl;
}

TEST_CASE("NeuralNetworkTest-testWithWordVectors") {
    SemanticDataSet mc, rg, ws, av, men, mturk, rare;
    mc = SemanticDataSet("MC.txt");
    rg = SemanticDataSet("RG.txt");
    ws = SemanticDataSet("WS353.txt");
    men = SemanticDataSet("MEN.txt");
    mturk = SemanticDataSet("MTurk771.txt");
    rare = SemanticDataSet("RareWords.txt");
    VectorizedDictionary dictionary = VectorizedDictionary("vectors-english-xs.txt", Comparator::ENGLISH);
    cout << dictionary.size() << endl;
    SemanticDataSet mc2 = mc.calculateSimilarities(dictionary);
    cout << "(" << mc.size() << ") " << mc.spearmanCorrelation(mc2) << endl;
    SemanticDataSet rg2 = rg.calculateSimilarities(dictionary);
    cout << "(" << rg.size() << ") " << rg.spearmanCorrelation(rg2) << endl;
    SemanticDataSet ws2 = ws.calculateSimilarities(dictionary);
    cout << "(" << ws.size() << ") " << ws.spearmanCorrelation(ws2) << endl;
    SemanticDataSet men2 = men.calculateSimilarities(dictionary);
    cout << "(" << men.size() << ") " << men.spearmanCorrelation(men2) << endl;
    SemanticDataSet mturk2 = mturk.calculateSimilarities(dictionary);
    cout << "(" << mturk.size() << ") " << mturk.spearmanCorrelation(mturk2) << endl;
    SemanticDataSet rare2 = rare.calculateSimilarities(dictionary);
    cout << "(" << rare.size() << ") " << rare.spearmanCorrelation(rare2) << endl;
}

TEST_CASE("NeuralNetworkTest-testTrainEnglishSkipGram") {
    SemanticDataSet mc, rg, ws, av, men, mturk, rare;
    auto* english = new Corpus("english-xs.txt");
    mc = SemanticDataSet("MC.txt");
    rg = SemanticDataSet("RG.txt");
    ws = SemanticDataSet("WS353.txt");
    men = SemanticDataSet("MEN.txt");
    mturk = SemanticDataSet("MTurk771.txt");
    rare = SemanticDataSet("RareWords.txt");
    WordToVecParameter parameter = WordToVecParameter();
    parameter.setCbow(false);
    NeuralNetwork neuralNetwork = NeuralNetwork(english, parameter);
    cout << neuralNetwork.vocabularySize() << endl;
    VectorizedDictionary dictionary = neuralNetwork.train();
    SemanticDataSet mc2 = mc.calculateSimilarities(dictionary);
    cout << "(" << mc.size() << ") " << mc.spearmanCorrelation(mc2) << endl;
    SemanticDataSet rg2 = rg.calculateSimilarities(dictionary);
    cout << "(" << rg.size() << ") " << rg.spearmanCorrelation(rg2) << endl;
    SemanticDataSet ws2 = ws.calculateSimilarities(dictionary);
    cout << "(" << ws.size() << ") " << ws.spearmanCorrelation(ws2) << endl;
    SemanticDataSet men2 = men.calculateSimilarities(dictionary);
    cout << "(" << men.size() << ") " << men.spearmanCorrelation(men2) << endl;
    SemanticDataSet mturk2 = mturk.calculateSimilarities(dictionary);
    cout << "(" << mturk.size() << ") " << mturk.spearmanCorrelation(mturk2) << endl;
    SemanticDataSet rare2 = rare.calculateSimilarities(dictionary);
    cout << "(" << rare.size() << ") " << rare.spearmanCorrelation(rare2) << endl;
}

TEST_CASE("NeuralNetworkTest-testTrainTurkishCBow") {
    SemanticDataSet av;
    auto* turkish = new Corpus("turkish-xs.txt");
    av = SemanticDataSet("AnlamverRel.txt");
    WordToVecParameter parameter = WordToVecParameter();
    parameter.setCbow(true);
    NeuralNetwork neuralNetwork = NeuralNetwork(turkish, parameter);
    cout << neuralNetwork.vocabularySize() << endl;
    VectorizedDictionary dictionary = neuralNetwork.train();
    SemanticDataSet av2 = av.calculateSimilarities(dictionary);
    cout << "(" << av.size() << ") " << av.spearmanCorrelation(av2) << endl;
}

TEST_CASE("NeuralNetworkTest-testTrainTurkishSkipGram") {
    SemanticDataSet av;
    auto* turkish = new Corpus("turkish-xs.txt");
    av = SemanticDataSet("AnlamverRel.txt");
    WordToVecParameter parameter = WordToVecParameter();
    parameter.setCbow(false);
    NeuralNetwork neuralNetwork = NeuralNetwork(turkish, parameter);
    cout << neuralNetwork.vocabularySize() << endl;
    VectorizedDictionary dictionary = neuralNetwork.train();
    SemanticDataSet av2 = av.calculateSimilarities(dictionary);
    cout << "(" << av.size() << ") " << av.spearmanCorrelation(av2) << endl;
}