//
// Created by olcay on 20.02.2019.
//

#ifndef WORDTOVEC_NEURALNETWORK_H
#define WORDTOVEC_NEURALNETWORK_H


#include <Matrix.h>
#include "Vocabulary.h"
#include "VectorizedDictionary.h"
#include "WordToVecParameter.h"

class NeuralNetwork {
private:
    Matrix wordVectors = Matrix(0), wordVectorUpdate = Matrix(0);
    Vocabulary vocabulary;
    WordToVecParameter parameter;
    Corpus corpus;
    vector<double> expTable;
    int EXP_TABLE_SIZE = 1000;
    int MAX_EXP = 6;
    void prepareExpTable();
    double calculateG(double f, double alpha, double label);
    void trainCbow();
    void trainSkipGram();
public:
    NeuralNetwork(Corpus& corpus, WordToVecParameter parameter);
    VectorizedDictionary train();
};


#endif //WORDTOVEC_NEURALNETWORK_H
