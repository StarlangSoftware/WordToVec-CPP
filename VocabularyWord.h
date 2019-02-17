//
// Created by Olcay Taner Yıldız on 17.02.2019.
//

#ifndef WORDTOVEC_VOCABULARYWORD_H
#define WORDTOVEC_VOCABULARYWORD_H
#include <Word.h>
#include <vector>

class VocabularyWord : public Word{
private:
    int count;
    vector<int> code;
    vector<int> point;
    int codeLength;
public:
    VocabularyWord(string name, int count);
    int getCount();
    void setCodeLength(int codeLength);
    void setCode(int index, int value);
    void setPoint(int index, int value);
    int getCodeLength();
    int getPoint(int index);
    int getCode(int index);
};


#endif //WORDTOVEC_VOCABULARYWORD_H
