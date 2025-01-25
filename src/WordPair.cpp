//
// Created by Olcay Taner YILDIZ on 15.11.2022.
//

#include "WordPair.h"

/**
 * Constructor of the WordPair object. WordPair stores the information about two words and their similarity scores.
 * @param _word1 First word
 * @param _word2 Second word
 * @param _relatedBy Similarity score between first and second word.
 */
WordPair::WordPair(const string& _word1, const string& _word2, double _relatedBy) {
    word1 = _word1;
    word2 = _word2;
    relatedBy = _relatedBy;
}

/**
 * Accessor for the similarity score.
 * @return Similarity score.
 */
double WordPair::getRelatedBy() const {
    return relatedBy;
}

/**
 * Mutator for the similarity score.
 * @param _relatedBy New similarity score
 */
void WordPair::setRelatedBy(double _relatedBy) {
    relatedBy = _relatedBy;
}

/**
 * Accessor for the first word.
 * @return First word.
 */
string WordPair::getWord1() const {
    return word1;
}

/**
 * Accessor for the second word.
 * @return Second word.
 */
string WordPair::getWord2() const {
    return word2;
}
