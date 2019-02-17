//
// Created by Olcay Taner Yıldız on 17.02.2019.
//

#include "Vocabulary.h"

struct VocabularyWordComparatorAccordingToCount{
    bool operator() (VocabularyWord* vocabularyWord1, VocabularyWord* vocabularyWord2){
        return vocabularyWord1->getCount() < vocabularyWord2->getCount();
    }
};

struct VocabularyWordComparatorAccordingToName{
    bool operator() (VocabularyWord* vocabularyWord1, VocabularyWord* vocabularyWord2){
        return vocabularyWord1->getName() < vocabularyWord2->getName();
    }
};

Vocabulary::Vocabulary(Corpus& corpus) {
    vector<Word> wordList;
    wordList = corpus.getWordList();
    for (Word word: wordList){
        vocabulary.push_back(new VocabularyWord(word.getName(), corpus.getCount(word)));
    }
    std::stable_sort(vocabulary.begin(), vocabulary.end(), VocabularyWordComparatorAccordingToCount());
    createUniGramTable();
    constructHuffmanTree();
    std::stable_sort(vocabulary.begin(), vocabulary.end(), VocabularyWordComparatorAccordingToName());
}

int Vocabulary::size() {
    return vocabulary.size();
}

int Vocabulary::getPosition(Word *word) {
    auto middle = lower_bound(vocabulary.begin(), vocabulary.end(), word, VocabularyWordComparatorAccordingToName());
    return middle - vocabulary.begin();
}

VocabularyWord *Vocabulary::getWord(int index) {
    return (VocabularyWord*) vocabulary[index];
}
