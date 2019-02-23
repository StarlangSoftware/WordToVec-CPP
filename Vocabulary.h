//
// Created by Olcay Taner Yıldız on 17.02.2019.
//

#ifndef WORDTOVEC_VOCABULARY_H
#define WORDTOVEC_VOCABULARY_H
#include <vector>
#include <Corpus.h>
#include "VocabularyWord.h"

class Vocabulary {
private:
    vector<VocabularyWord*> vocabulary;
    vector<int> table;
    void constructHuffmanTree();
    void createUniGramTable();
    int MAX_CODE_LENGTH = 40;
public:
    Vocabulary();
    explicit Vocabulary(Corpus& corpus);
    int size();
    int getPosition(VocabularyWord* word);
    VocabularyWord* getWord(int index);
    int getTableValue(int index);
    int getTableSize();
};


#endif //WORDTOVEC_VOCABULARY_H
