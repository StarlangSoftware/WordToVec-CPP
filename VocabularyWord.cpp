//
// Created by Olcay Taner Yıldız on 17.02.2019.
//

#include "VocabularyWord.h"

/**
 * Constructor for a {@link VocabularyWord}. The constructor gets name and count values and sets the corresponding
 * attributes. It also initializes the code and point arrays for this word.
 * @param name Lemma of the word
 * @param count Number of occurences of this word in the corpus
 */
VocabularyWord::VocabularyWord(string name, int count) : Word(move(name)) {
    this->count = count;
    this->codeLength = 0;
}

/**
 * Accessor for the count attribute.
 * @return Number of occurences of this word.
 */
int VocabularyWord::getCount() {
    return count;
}

/**
 * Mutator for codeLength attribute.
 * @param codeLength New value for the codeLength.
 */
void VocabularyWord::setCodeLength(int codeLength) {
    this->codeLength = codeLength;
    this->code.resize(codeLength);
    this->point.resize(codeLength);
}

/**
 * Mutator for code attribute.
 * @param index Index of the code
 * @param value New value for that indexed element of code.
 */
void VocabularyWord::setCode(int index, int value) {
    code[index] = value;
}

/**
 * Mutator for point attribute.
 * @param index Index of the point
 * @param value New value for that indexed element of point.
 */
void VocabularyWord::setPoint(int index, int value) {
    point[index] = value;
}

/**
 * Accessor for the codeLength attribute.
 * @return Length of the Huffman code for this word.
 */
int VocabularyWord::getCodeLength() {
    return codeLength;
}

/**
 * Accessor for point attribute.
 * @param index Index of the point.
 * @return Value for that indexed element of point.
 */
int VocabularyWord::getPoint(int index) {
    return point[index];
}

/**
 * Accessor for code attribute.
 * @param index Index of the code.
 * @return Value for that indexed element of code.
 */
int VocabularyWord::getCode(int index) {
    return code[index];
}
