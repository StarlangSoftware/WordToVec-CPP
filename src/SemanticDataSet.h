//
// Created by Olcay Taner YILDIZ on 15.11.2022.
//

#ifndef WORDTOVEC_SEMANTICDATASET_H
#define WORDTOVEC_SEMANTICDATASET_H

#include <vector>
#include "Dictionary/VectorizedDictionary.h"
#include "WordPair.h"

class SemanticDataSet {
private:
    vector<WordPair> pairs;
public:
    SemanticDataSet();
    explicit SemanticDataSet(const string& fileName);
    SemanticDataSet calculateSimilarities(VectorizedDictionary& dictionary);
    int size() const;
    void sort();
    int index(const WordPair& wordPair);
    double spearmanCorrelation(SemanticDataSet& semanticDataSet);
};


#endif //WORDTOVEC_SEMANTICDATASET_H
