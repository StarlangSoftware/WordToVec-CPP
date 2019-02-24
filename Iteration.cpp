//
// Created by Olcay Taner Yıldız on 23.02.2019.
//

#include "Iteration.h"

Iteration::Iteration(Corpus* corpus, WordToVecParameter& parameter) {
    this->parameter = parameter;
    this->corpus = corpus;
    startingAlpha = parameter.getAlpha();
    alpha = parameter.getAlpha();
}

void Iteration::alphaUpdate() {
    if (wordCount - lastWordCount > 10000) {
        wordCountActual += wordCount - lastWordCount;
        lastWordCount = wordCount;
        alpha = startingAlpha * (1 - wordCountActual / (parameter.getNumberOfIterations() * corpus->numberOfWords() + 1.0));
        if (alpha < startingAlpha * 0.0001)
            alpha = startingAlpha * 0.0001;
    }
}

Sentence* Iteration::sentenceUpdate(Sentence* currentSentence) {
    sentencePosition++;
    if (sentencePosition >= currentSentence->wordCount()) {
        wordCount += currentSentence->wordCount();
        sentenceIndex++;
        sentencePosition = 0;
        if (sentenceIndex == corpus->sentenceCount()){
            iterationCount++;
            wordCount = 0;
            lastWordCount = 0;
            sentenceIndex = 0;
            corpus->shuffleSentences(1);
        }
        return corpus->getSentence(sentenceIndex);
    }
    return currentSentence;
}

double Iteration::getAlpha() {
    return alpha;
}

int Iteration::getIterationCount() {
    return iterationCount;
}

int Iteration::getSentenceIndex() {
    return sentenceIndex;
}

int Iteration::getSentencePosition() {
    return sentencePosition;
}
