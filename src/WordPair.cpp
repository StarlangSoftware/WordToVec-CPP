//
// Created by Olcay Taner YILDIZ on 15.11.2022.
//

#include "WordPair.h"

WordPair::WordPair(const string& _word1, const string& _word2, double _relatedBy) {
    word1 = _word1;
    word2 = _word2;
    relatedBy = _relatedBy;
}

double WordPair::getRelatedBy() const {
    return relatedBy;
}

void WordPair::setRelatedBy(double _relatedBy) {
    relatedBy = _relatedBy;
}

string WordPair::getWord1() const {
    return word1;
}

string WordPair::getWord2() const {
    return word2;
}
