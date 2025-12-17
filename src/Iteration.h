//
// Created by Olcay Taner Yıldız on 23.02.2019.
//

#ifndef WORDTOVEC_ITERATION_H
#define WORDTOVEC_ITERATION_H


#include "CorpusStream.h"
#include "WordToVecParameter.h"

class Iteration {
private:
    int wordCount = 0, lastWordCount = 0, wordCountActual = 0;
    int iterationCount = 0;
    int sentencePosition = 0;
    double startingAlpha, alpha;
    WordToVecParameter parameter;
    AbstractCorpus* corpus;
public:
    explicit Iteration(AbstractCorpus* corpus, const WordToVecParameter& parameter);
    void alphaUpdate(int totalNumberOfWords);
    Sentence* sentenceUpdate(Sentence* currentSentence);
    [[nodiscard]] double getAlpha() const;
    [[nodiscard]] int getIterationCount() const;
    [[nodiscard]] int getSentencePosition() const;
};


#endif //WORDTOVEC_ITERATION_H
