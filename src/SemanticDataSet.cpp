//
// Created by Olcay Taner YILDIZ on 15.11.2022.
//

#include <fstream>
#include <iostream>
#include "Dictionary/Word.h"
#include "SemanticDataSet.h"

SemanticDataSet::SemanticDataSet(const string &fileName) {
    ifstream inputStream;
    inputStream.open(fileName, ifstream::in);
    string line;
    while (inputStream.good()){
        getline(inputStream, line);
        vector<string> items = Word::split(line);
        pairs.emplace_back(items[0], items[1], stof(items[2]));
    }
    inputStream.close();
}

SemanticDataSet SemanticDataSet::calculateSimilarities(VectorizedDictionary &dictionary) {
    SemanticDataSet result = SemanticDataSet();
    double similarity;
    for (int i = 0; i < pairs.size(); i++){
        string word1 = pairs[i].getWord1();
        string word2 = pairs[i].getWord2();
        auto* vectorizedWord1 = (VectorizedWord*) dictionary.getWord(word1);
        auto* vectorizedWord2 = (VectorizedWord*) dictionary.getWord(word2);
        if (vectorizedWord1 != nullptr && vectorizedWord2 != nullptr){
            similarity = vectorizedWord1->getVector().cosineSimilarity(vectorizedWord2->getVector());
            result.pairs.push_back(WordPair(word1, word2, similarity));
        } else {
            pairs.erase(pairs.begin() + i);
            i--;
        }
    }
    return result;
}

int SemanticDataSet::size() const{
    return pairs.size();
}

void SemanticDataSet::sort() {
    std::sort(pairs.begin(), pairs.end());
}

int SemanticDataSet::index(const WordPair &wordPair) {
    for (int i = 0; i < pairs.size(); i++){
        if (wordPair == pairs[i]){
            return i;
        }
    }
    return -1;
}

double SemanticDataSet::spearmanCorrelation(SemanticDataSet &semanticDataSet) {
    double sum = 0;
    int rank1, rank2;
    sort();
    semanticDataSet.sort();
    for (int i = 0; i < pairs.size(); i++){
        rank1 = i + 1;
        if (semanticDataSet.index(pairs[i]) != -1){
            rank2 = semanticDataSet.index(pairs[i]) + 1;
        }
        double di = rank1 - rank2;
        sum += 6 * di * di;
    }
    double n = pairs.size();
    double ratio = sum / (n * (n * n - 1));
    return 1 - ratio;
}

SemanticDataSet::SemanticDataSet() = default;
