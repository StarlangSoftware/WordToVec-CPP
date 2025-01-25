//
// Created by Olcay Taner YILDIZ on 15.11.2022.
//

#include <fstream>
#include <iostream>
#include "StringUtils.h"
#include "SemanticDataSet.h"

/**
 * Constructor for the semantic dataset. Reads word pairs and their similarity scores from an input file.
 * @param fileName Input file that stores the word pair and similarity scores.
 */
SemanticDataSet::SemanticDataSet(const string &fileName) {
    ifstream inputStream;
    inputStream.open(fileName, ifstream::in);
    string line;
    while (inputStream.good()){
        getline(inputStream, line);
        vector<string> items = StringUtils::split(line);
        pairs.emplace_back(items[0], items[1], stof(items[2]));
    }
    inputStream.close();
}

/**
 * Calculates the similarities between words in the dataset. The word vectors will be taken from the input
 * vectorized dictionary.
 * @param dictionary Vectorized dictionary that stores the word vectors.
 * @return Word pairs and their calculated similarities stored as a semantic dataset.
 */
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
            result.pairs.emplace_back(word1, word2, similarity);
        } else {
            pairs.erase(pairs.begin() + i);
            i--;
        }
    }
    return result;
}

/**
 * Returns the size of the semantic dataset.
 * @return The size of the semantic dataset.
 */
int SemanticDataSet::size() const{
    return pairs.size();
}

/**
 * Sorts the word pairs in the dataset according to the WordPairComparator.
 */
void SemanticDataSet::sort() {
    std::sort(pairs.begin(), pairs.end());
}

/**
 * Finds and returns the index of a word pair in the pairs array list. If there is no such word pair, it
 * returns -1.
 * @param wordPair Word pair to search in the semantic dataset.
 * @return Index of the given word pair in the pairs array list. If it does not exist, the method returns -1.
 */
int SemanticDataSet::index(const WordPair &wordPair) const {
    for (int i = 0; i < pairs.size(); i++){
        if (wordPair == pairs[i]){
            return i;
        }
    }
    return -1;
}

/**
 * Calculates the Spearman correlation coefficient with this dataset to the given semantic dataset.
 * @param semanticDataSet Given semantic dataset with which Spearman correlation coefficient is calculated.
 * @return Spearman correlation coefficient with the given semantic dataset.
 */
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

/**
 * Empty constructor for the semantic dataset.
 */
SemanticDataSet::SemanticDataSet() = default;
