//
// Created by Olcay Taner YILDIZ on 15.11.2022.
//

#ifndef WORDTOVEC_WORDPAIR_H
#define WORDTOVEC_WORDPAIR_H

#include <string>

using namespace std;

class WordPair {
private:
    string word1;
    string word2;
    double relatedBy;
public:
    WordPair(const string& _word1, const string& _word2, double _relatedBy);
    double getRelatedBy() const;
    void setRelatedBy(double _relatedBy);
    string getWord1() const;
    string getWord2() const;
    bool operator==(const WordPair &anotherWordPair) const{
        return (word1 == anotherWordPair.word1) && (word2 == anotherWordPair.word2);
    }
    bool operator<(const WordPair &anotherWordPair) const{
        return (relatedBy > anotherWordPair.relatedBy);
    }
};


#endif //WORDTOVEC_WORDPAIR_H
