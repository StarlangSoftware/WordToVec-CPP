//
// Created by Olcay Taner Yıldız on 2.01.2019.
//

#ifndef DICTIONARY_DICTIONARY_H
#define DICTIONARY_DICTIONARY_H

#include<vector>
#include <locale>
#include "Word.h"

using namespace std;

enum class Comparator{
    ENGLISH, TURKISH, TURKISH_NO_CASE
};

class Dictionary {
protected:
    vector<Word*> words;
    string filename;
    Comparator comparator;
    void sort();
public:
    Dictionary();
    explicit Dictionary(Comparator comparator);
    Word* getWord(string name);
    int getWordIndex(string name);
    bool wordExists(string name);
    unsigned long size();
    Word* getWord(unsigned long index);
    unsigned long longestWordSize();
    unsigned long getWordStartingWith(string hash);
};


#endif //DICTIONARY_DICTIONARY_H
