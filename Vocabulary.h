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
    vector<Word*> vocabulary;
    vector<int> table;
public:
    explicit Vocabulary(Corpus& corpus);
    int size();
    int getPosition(Word* word);
    VocabularyWord* getWord(int index);
};


#endif //WORDTOVEC_VOCABULARY_H
