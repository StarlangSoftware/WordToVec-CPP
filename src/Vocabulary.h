//
// Created by Olcay Taner Yıldız on 17.02.2019.
//

#ifndef WORDTOVEC_VOCABULARY_H
#define WORDTOVEC_VOCABULARY_H
#include <vector>
#include <unordered_map>
#include "CorpusStream.h"
#include "VocabularyWord.h"

class Vocabulary {
private:
    vector<VocabularyWord*> vocabulary;
    vector<int> table;
    unordered_map<string, int> wordMap;
    void constructHuffmanTree();
    void createUniGramTable();
    int MAX_CODE_LENGTH = 40;
    int totalNumberOfWords = 0;
public:
    Vocabulary();
    explicit Vocabulary(AbstractCorpus* corpus);
    int size() const;
    int getTotalNumberOfWords() const;
    int getPosition(VocabularyWord* word) const;
    VocabularyWord* getWord(int index) const;
    int getTableValue(int index) const;
    int getTableSize() const;
};


#endif //WORDTOVEC_VOCABULARY_H
