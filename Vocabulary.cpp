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

int Vocabulary::getPosition(VocabularyWord *word) {
    auto middle = lower_bound(vocabulary.begin(), vocabulary.end(), word, VocabularyWordComparatorAccordingToName());
    return middle - vocabulary.begin();
}

VocabularyWord *Vocabulary::getWord(int index) {
    return (VocabularyWord*) vocabulary[index];
}

void Vocabulary::constructHuffmanTree() {
    int min1i, min2i, b, i;
    int* count = new int[vocabulary.size() * 2 + 1];
    int* code = new int[MAX_CODE_LENGTH];
    int* point = new int[MAX_CODE_LENGTH];
    int* binary = new int[vocabulary.size() * 2 + 1];
    int* parentNode = new int[vocabulary.size() * 2 + 1];
    for (int a = 0; a < vocabulary.size(); a++)
        count[a] = vocabulary.at(a)->getCount();
    for (int a = vocabulary.size(); a < vocabulary.size() * 2; a++)
        count[a] = 1000000000;
    int pos1 = vocabulary.size() - 1;
    int pos2 = vocabulary.size();
    for (int a = 0; a < vocabulary.size() - 1; a++) {
        if (pos1 >= 0) {
            if (count[pos1] < count[pos2]) {
                min1i = pos1;
                pos1--;
            } else {
                min1i = pos2;
                pos2++;
            }
        } else {
            min1i = pos2;
            pos2++;
        }
        if (pos1 >= 0) {
            if (count[pos1] < count[pos2]) {
                min2i = pos1;
                pos1--;
            } else {
                min2i = pos2;
                pos2++;
            }
        } else {
            min2i = pos2;
            pos2++;
        }
        count[vocabulary.size() + a] = count[min1i] + count[min2i];
        parentNode[min1i] = vocabulary.size() + a;
        parentNode[min2i] = vocabulary.size() + a;
        binary[min2i] = 1;
    }
    for (int a = 0; a < vocabulary.size(); a++) {
        b = a;
        i = 0;
        while (true) {
            code[i] = binary[b];
            point[i] = b;
            i++;
            b = parentNode[b];
            if (b == vocabulary.size() * 2 - 2)
                break;
        }
        vocabulary.at(a)->setCodeLength(i);
        vocabulary.at(a)->setPoint(0, vocabulary.size() - 2);
        for (b = 0; b < i; b++) {
            vocabulary.at(a)->setCode(i - b - 1, code[b]);
            vocabulary.at(a)->setPoint(i - b, point[b] - vocabulary.size());
        }
    }
    delete[] count;
    delete[] code;
    delete[] point;
    delete[] binary;
    delete[] parentNode;
}

void Vocabulary::createUniGramTable() {
    int i;
    double total = 0;
    double d1;
    table.reserve(2 * vocabulary.size());
    for (auto &a : vocabulary) {
        total += pow(a->getCount(), 0.75);
    }
    i = 0;
    d1 = pow(vocabulary.at(i)->getCount(), 0.75) / total;
    for (int a = 0; a < 2 * vocabulary.size(); a++) {
        table.push_back(i);
        if (a / (2 * vocabulary.size() + 0.0) > d1) {
            i++;
            d1 += pow(vocabulary.at(i)->getCount(), 0.75) / total;
        }
        if (i >= vocabulary.size())
            i = vocabulary.size() - 1;
    }
}

int Vocabulary::getTableValue(int index) {
    return table[index];
}

int Vocabulary::getTableSize() {
    return table.size();
}

Vocabulary::Vocabulary() {

}
