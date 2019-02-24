//
// Created by Olcay Taner Yıldız on 17.02.2019.
//

#include "VocabularyWord.h"

VocabularyWord::VocabularyWord(string name, int count) : Word(move(name)) {
    this->count = count;
    this->codeLength = 0;
}

int VocabularyWord::getCount() {
    return count;
}

void VocabularyWord::setCodeLength(int codeLength) {
    this->codeLength = codeLength;
    this->code.resize(codeLength);
    this->point.resize(codeLength);
}

void VocabularyWord::setCode(int index, int value) {
    code[index] = value;
}

void VocabularyWord::setPoint(int index, int value) {
    point[index] = value;
}

int VocabularyWord::getCodeLength() {
    return codeLength;
}

int VocabularyWord::getPoint(int index) {
    return point[index];
}

int VocabularyWord::getCode(int index) {
    return code[index];
}
