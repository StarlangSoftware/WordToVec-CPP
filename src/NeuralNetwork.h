//
// Created by olcay on 20.02.2019.
//

#ifndef WORDTOVEC_NEURALNETWORK_H
#define WORDTOVEC_NEURALNETWORK_H


#include "Vocabulary.h"
#include "Dictionary/VectorizedDictionary.h"
#include "WordToVecParameter.h"

class NeuralNetwork {
private:
    double** wordVectors, **wordVectorUpdate;
    Vocabulary vocabulary;
    WordToVecParameter parameter;
    AbstractCorpus* corpus;
    vector<double> expTable;
    int vectorLength;
    int EXP_TABLE_SIZE = 1000;
    int MAX_EXP = 6;
    void prepareExpTable();
    [[nodiscard]] double calculateG(double f, double alpha, double label) const;
    void trainCbow() const;
    void trainSkipGram() const;
    void updateOutput(double* outputUpdate, const double* outputs, int l2, double g) const;
    double dotProduct(const double* vector1, const double* vector2) const;
public:
    NeuralNetwork(AbstractCorpus* corpus, const WordToVecParameter& parameter);
    [[nodiscard]] int vocabularySize() const;
    [[nodiscard]] VectorizedDictionary train() const;
};


#endif //WORDTOVEC_NEURALNETWORK_H
