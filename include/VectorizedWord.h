//
// Created by Olcay Taner Yıldız on 2.01.2019.
//

#ifndef DICTIONARY_VECTORIZEDWORD_H
#define DICTIONARY_VECTORIZEDWORD_H


#include <Vector.h>
#include "Word.h"

class VectorizedWord : public Word {
private:
    Vector vector = Vector(0, 0.0);
public:
    VectorizedWord(string name, Vector vector);
    Vector getVector();
};


#endif //DICTIONARY_VECTORIZEDWORD_H
