//
// Created by Olcay Taner Yıldız on 23.02.2019.
//

#ifndef WORDTOVEC_ITERATION_H
#define WORDTOVEC_ITERATION_H


#include <Corpus.h>
#include "WordToVecParameter.h"

class Iteration {
private:
    int wordCount = 0, lastWordCount = 0, wordCountActual = 0;
    int iterationCount = 0;
    int sentencePosition = 0, sentenceIndex = 0;
    double startingAlpha, alpha;
    WordToVecParameter parameter;
    Corpus* corpus;
public:
    explicit Iteration(Corpus* corpus, WordToVecParameter& parameter);
    void alphaUpdate();
    Sentence* sentenceUpdate(Sentence* currentSentence);
    double getAlpha();
    int getIterationCount();
    int getSentenceIndex();
    int getSentencePosition();
};


#endif //WORDTOVEC_ITERATION_H
