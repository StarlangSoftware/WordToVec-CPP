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
    void constructHuffmanTree() const;
    void createUniGramTable();
    int totalNumberOfWords = 0;
public:
    Vocabulary();
    explicit Vocabulary(AbstractCorpus* corpus);
    [[nodiscard]] int size() const;
    [[nodiscard]] int getTotalNumberOfWords() const;
    int getPosition(const VocabularyWord* word) const;
    [[nodiscard]] VocabularyWord* getWord(int index) const;
    [[nodiscard]] int getTableValue(int index) const;
    [[nodiscard]] int getTableSize() const;
};


#endif //WORDTOVEC_VOCABULARY_H
