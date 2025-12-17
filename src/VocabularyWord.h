//
// Created by Olcay Taner Yıldız on 17.02.2019.
//

#ifndef WORDTOVEC_VOCABULARYWORD_H
#define WORDTOVEC_VOCABULARYWORD_H
#include "Dictionary/Word.h"
#include <vector>

class VocabularyWord : public Word{
private:
    int count;
    int code[40];
    int point[40];
    int codeLength;
public:
    VocabularyWord(const string& name, int count);
    [[nodiscard]] int getCount() const;
    void setCodeLength(int _codeLength);
    void setCode(int index, int value);
    void setPoint(int index, int value);
    [[nodiscard]] int getCodeLength() const;
    [[nodiscard]] int getPoint(int index) const;
    [[nodiscard]] int getCode(int index) const;
};


#endif //WORDTOVEC_VOCABULARYWORD_H
