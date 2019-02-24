//
// Created by Olcay Taner Yıldız on 23.02.2019.
//

#include <Corpus.h>
#include "WordToVecParameter.h"
#include "NeuralNetwork.h"

VectorizedDictionary learnCBow(Corpus& corpus){
    WordToVecParameter parameter = WordToVecParameter();
    parameter.setCbow(true);
    NeuralNetwork neuralNetwork = NeuralNetwork(corpus, parameter);
    return neuralNetwork.train();
}

VectorizedDictionary learnSkipGram(Corpus& corpus){
    WordToVecParameter parameter = WordToVecParameter();
    parameter.setCbow(false);
    NeuralNetwork neuralNetwork = NeuralNetwork(corpus, parameter);
    return neuralNetwork.train();
}

int main(){
    Corpus corpus = Corpus("corpus.txt");
    learnCBow(corpus);
}
