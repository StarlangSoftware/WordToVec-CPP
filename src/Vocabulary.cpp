//
// Created by Olcay Taner Yıldız on 17.02.2019.
//

#include "Vocabulary.h"

#include <algorithm>

#include "CounterHashMap.h"
#include <cmath>

struct VocabularyWordComparatorAccordingToCount{
    bool operator() (VocabularyWord* vocabularyWord1, VocabularyWord* vocabularyWord2) const {
        return vocabularyWord1->getCount() > vocabularyWord2->getCount();
    }
};

struct VocabularyWordComparatorAccordingToName{
    bool operator() (VocabularyWord* vocabularyWord1, VocabularyWord* vocabularyWord2) const {
        return vocabularyWord1->getName() < vocabularyWord2->getName();
    }
};

/**
 * Constructor for the Vocabulary class. For each distinct word in the corpus, a VocabularyWord
 * instance is created. After that, words are sorted according to their occurences. Unigram table is constructed,
 * whereafter Huffman tree is created based on the number of occurences of the words.
 * @param corpus Corpus used to train word vectors using Word2Vec algorithm.
 */
Vocabulary::Vocabulary(AbstractCorpus* corpus) {
    CounterHashMap<string> counts = CounterHashMap<string>();
    corpus->open();
    Sentence* sentence = corpus->getSentence();
    while (sentence != nullptr){
        for (int i = 0; i < sentence->wordCount(); i++){
            counts.put(sentence->getWord(i)->getName());
        }
        totalNumberOfWords += sentence->wordCount();
        sentence = corpus->getSentence();
    }
    corpus->close();
    for (auto & count : counts){
        vocabulary.push_back(new VocabularyWord(count.first, count.second));
    }
    sort(vocabulary.begin(), vocabulary.end(), VocabularyWordComparatorAccordingToCount());
    createUniGramTable();
    constructHuffmanTree();
    sort(vocabulary.begin(), vocabulary.end(), VocabularyWordComparatorAccordingToName());
    for (int i = 0; i < vocabulary.size(); i++){
        wordMap[vocabulary[i]->getName()] = i;
    }
}

/**
 * Returns number of words in the vocabulary.
 * @return Number of words in the vocabulary.
 */
int Vocabulary::size() const{
    return vocabulary.size();
}

/**
 * Searches a word and returns the position of that word in the vocabulary. Search is done using binary search.
 * @param word Word to be searched.
 * @return Position of the word searched.
 */
int Vocabulary::getPosition(VocabularyWord *word) const{
    return wordMap.at(word->getName());
}

/**
 * Returns the word at a given index.
 * @param index Index of the word.
 * @return The word at a given index.
 */
VocabularyWord *Vocabulary::getWord(int index) const{
    return (VocabularyWord*) vocabulary[index];
}

/**
 * Constructs Huffman Tree based on the number of occurences of the words.
 */
void Vocabulary::constructHuffmanTree() const {
    int min1i, min2i, b, i, size = vocabulary.size();
    int* count = new int[size * 2 + 1];
    int* code = new int[40];
    int* point = new int[40];
    int* binary = new int[size * 2 + 1];
    int* parentNode = new int[size * 2 + 1];
    for (int a = 0; a < size; a++)
        count[a] = vocabulary.at(a)->getCount();
    for (int a = size; a < size * 2; a++)
        count[a] = 1000000000;
    int pos1 = size - 1;
    int pos2 = size;
    for (int a = 0; a < size - 1; a++) {
        if (pos1 >= 0) {
            if (count[pos1] < count[pos2]) {
                min1i = pos1;
                pos1--;
            } else {
                min1i = pos2;
                pos2++;
            }
        } else {
            min1i = pos2;
            pos2++;
        }
        if (pos1 >= 0) {
            if (count[pos1] < count[pos2]) {
                min2i = pos1;
                pos1--;
            } else {
                min2i = pos2;
                pos2++;
            }
        } else {
            min2i = pos2;
            pos2++;
        }
        count[vocabulary.size() + a] = count[min1i] + count[min2i];
        parentNode[min1i] = size + a;
        parentNode[min2i] = size + a;
        binary[min2i] = 1;
    }
    for (int a = 0; a < size; a++) {
        b = a;
        i = 0;
        while (true) {
            code[i] = binary[b];
            point[i] = b;
            i++;
            b = parentNode[b];
            if (b == vocabulary.size() * 2 - 2)
                break;
        }
        vocabulary.at(a)->setCodeLength(i);
        vocabulary.at(a)->setPoint(0, size - 2);
        for (b = 0; b < i; b++) {
            vocabulary.at(a)->setCode(i - b - 1, code[b]);
            vocabulary.at(a)->setPoint(i - b, point[b] - size);
        }
    }
    delete[] count;
    delete[] code;
    delete[] point;
    delete[] binary;
    delete[] parentNode;
}

/**
 * Constructs the unigram table based on the number of occurrences of the words.
 */
void Vocabulary::createUniGramTable() {
    int i;
    double total = 0;
    double d1;
    table.reserve(2 * vocabulary.size());
    for (auto &a : vocabulary) {
        total += pow(a->getCount(), 0.75);
    }
    i = 0;
    d1 = pow(vocabulary.at(i)->getCount(), 0.75) / total;
    for (int a = 0; a < 2 * vocabulary.size(); a++) {
        table.push_back(i);
        if (a / (2 * vocabulary.size() + 0.0) > d1) {
            i++;
            d1 += pow(vocabulary.at(i)->getCount(), 0.75) / total;
        }
        if (i >= vocabulary.size())
            i = vocabulary.size() - 1;
    }
}

/**
 * Accessor for the unigram table.
 * @param index Index of the word.
 * @return Unigram table value at a given index.
 */
int Vocabulary::getTableValue(int index) const{
    return table[index];
}

/**
 * Returns size of the unigram table.
 * @return Size of the unigram table.
 */
int Vocabulary::getTableSize() const{
    return table.size();
}

/**
 * Accessor for the total number of words
 * @return Total number of words
 */
int Vocabulary::getTotalNumberOfWords() const {
    return totalNumberOfWords;
}

Vocabulary::Vocabulary() = default;
