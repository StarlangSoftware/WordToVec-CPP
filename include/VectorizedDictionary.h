//
// Created by olcay on 20.02.2019.
//

#ifndef DICTIONARY_VECTORIZEDDICTIONARY_H
#define DICTIONARY_VECTORIZEDDICTIONARY_H


#include "Dictionary.h"
#include "VectorizedWord.h"

class VectorizedDictionary : public Dictionary {
public:
    explicit VectorizedDictionary(Comparator comparator);
    void addWord(VectorizedWord* word);
    VectorizedWord* mostSimilarWord(string name);
    vector<Word*>* kMeansClustering(int iteration, int k);
    vector<VectorizedWord*> mostSimilarKWords(string name, int k);
};


#endif //DICTIONARY_VECTORIZEDDICTIONARY_H
