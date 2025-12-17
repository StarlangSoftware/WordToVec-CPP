//
// Created by Olcay Taner Yıldız on 23.02.2019.
//

#include "Iteration.h"

#include <iostream>

/**
 * Constructor for the Iteration class. Get corpus and parameter as input, sets the corresponding
 * parameters.
 * @param corpus Corpus used to train word vectors using Word2Vec algorithm.
 * @param parameter Parameters of the Word2Vec algorithm.
 */
Iteration::Iteration(AbstractCorpus* corpus, const WordToVecParameter& parameter) {
    this->parameter = parameter;
    this->corpus = corpus;
    startingAlpha = parameter.getAlpha();
    alpha = parameter.getAlpha();
}

/**
 * Updates the alpha parameter after 10000 words has been processed.
 */
void Iteration::alphaUpdate(int totalNumberOfWords) {
    if (wordCount - lastWordCount > 10000) {
        wordCountActual += wordCount - lastWordCount;
        lastWordCount = wordCount;
        alpha = startingAlpha * (1 - wordCountActual / (parameter.getNumberOfIterations() * totalNumberOfWords + 1.0));
        if (alpha < startingAlpha * 0.0001)
            alpha = startingAlpha * 0.0001;
    }
}

/**
 * Updates sentencePosition, sentenceIndex (if needed) and returns the current sentence processed. If one sentence
 * is finished, the position shows the beginning of the next sentence and sentenceIndex is incremented. If the
 * current sentence is the last sentence, the system shuffles the sentences and returns the first sentence.
 * @param currentSentence Current sentence processed.
 * @return If current sentence is not changed, currentSentence; if changed the next sentence; if next sentence is
 * the last sentence; shuffles the corpus and returns the first sentence.
 */
Sentence* Iteration::sentenceUpdate(Sentence* currentSentence) {
    sentencePosition++;
    if (sentencePosition >= currentSentence->wordCount()) {
        wordCount += currentSentence->wordCount();
        sentencePosition = 0;
        Sentence* sentence = corpus->getSentence();
        if (sentence == nullptr){
            iterationCount++;
            cout << "Iteration " << iterationCount << endl;
            wordCount = 0;
            lastWordCount = 0;
            corpus->close();
            corpus->open();
            sentence = corpus->getSentence();
        }
        return sentence;
    }
    return currentSentence;
}

/**
 * Accessor for the alpha attribute.
 * @return Alpha attribute.
 */
double Iteration::getAlpha() const{
    return alpha;
}

/**
 * Accessor for the iterationCount attribute.
 * @return IterationCount attribute.
 */
int Iteration::getIterationCount() const{
    return iterationCount;
}

/**
 * Accessor for the sentencePosition attribute.
 * @return SentencePosition attribute
 */
int Iteration::getSentencePosition() const{
    return sentencePosition;
}
