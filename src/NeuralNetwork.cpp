//
// Created by olcay on 20.02.2019.
//

#include "Dictionary/Dictionary.h"
#include "NeuralNetwork.h"
#include "Iteration.h"

/**
 * Constructor for the {@link NeuralNetwork} class. Gets corpus and network parameters as input and sets the
 * corresponding parameters first. After that, initializes the network with random weights between -0.5 and 0.5.
 * Constructs vector update matrix and prepares the exp table.
 * @param corpus Corpus used to train word vectors using Word2Vec algorithm.
 * @param parameter Parameters of the Word2Vec algorithm.
 */
NeuralNetwork::NeuralNetwork(AbstractCorpus* corpus, const WordToVecParameter& parameter) {
    int row;
    srand(parameter.getSeed());
    this->vocabulary = Vocabulary(corpus);
    this->parameter = parameter;
    vectorLength = parameter.getLayerSize();
    this->corpus = corpus;
    row = vocabulary.size();
    wordVectors = new double*[row];
    for (int i = 0; i < row; i++){
        wordVectors[i] = new double [vectorLength];
    }
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < vectorLength; j++) {
            wordVectors[i][j] = -0.5 + ((double)rand()) / RAND_MAX;
        }
    }
    wordVectorUpdate = new double*[row];
    for (int i = 0; i < row; i++){
        wordVectorUpdate[i] = new double[vectorLength];
    }
    prepareExpTable();
}

/**
 * Constructs the fast exponentiation table. Instead of taking exponent at each time, the algorithm will lookup
 * the table.
 */
void NeuralNetwork::prepareExpTable() {
    expTable.reserve(EXP_TABLE_SIZE + 1);
    for (int i = 0; i < EXP_TABLE_SIZE; i++) {
        expTable.push_back(exp((i / (EXP_TABLE_SIZE + 0.0) * 2 - 1) * MAX_EXP));
        expTable[i] = expTable[i] / (expTable[i] + 1);
    }
}

/**
 * Calculates G value in the Word2Vec algorithm.
 * @param f F value.
 * @param alpha Learning rate alpha.
 * @param label Label of the instance.
 * @return Calculated G value.
 */
double NeuralNetwork::calculateG(double f, double alpha, double label) {
    if (f > MAX_EXP){
        return (label - 1) * alpha;
    } else {
        if (f < -MAX_EXP){
            return label * alpha;
        } else {
            int index = (int) ((f + MAX_EXP) * (EXP_TABLE_SIZE / MAX_EXP / 2));
            if (index >= 0 && index < EXP_TABLE_SIZE){
                return (label - expTable[index]) * alpha;
            } else {
                return (label - 1) * alpha;
            }
        }
    }
}

/**
 * Main method for training the Word2Vec algorithm. Depending on the training parameter, CBox or SkipGram algorithm
 * is applied.
 * @return Dictionary of word vectors.
 */
VectorizedDictionary NeuralNetwork::train() {
    VectorizedDictionary result = VectorizedDictionary(Comparator::ENGLISH);
    if (parameter.isCbow()){
        trainCbow();
    } else {
        trainSkipGram();
    }
    for (int i = 0; i < vocabulary.size(); i++){
        Vector vector = Vector((long) 0, 0);
        for (int j = 0; j < vectorLength; j++){
            vector.add(wordVectors[i][j]);
        }
        result.addWord(new VectorizedWord(vocabulary.getWord(i)->getName(), vector));
    }
    return result;
}

void NeuralNetwork::updateOutput(double* outputUpdate, const double* outputs, int l2, double g){
    for (int j = 0; j < vectorLength; j++){
        outputUpdate[j] += wordVectorUpdate[l2][j] * g;
    }
    for (int j = 0; j < vectorLength; j++){
        wordVectorUpdate[l2][j] += outputs[j] * g;
    }
}

double NeuralNetwork::dotProduct(const double* vector1, const double* vector2) const{
    double sum = 0;
    for (int j = 0; j < vectorLength; j++){
        sum += vector1[j] * vector2[j];
    }
    return sum;
}

/**
 * Main method for training the CBow version of Word2Vec algorithm.
 */
void NeuralNetwork::trainCbow() {
    int wordIndex, lastWordIndex;
    Iteration iteration = Iteration(corpus, parameter);
    int target, label, l2, b, cw;
    double f, g;
    corpus->open();
    Sentence* currentSentence = corpus->getSentence();
    VocabularyWord* currentWord;
    auto* outputs = new double[vectorLength];
    auto* outputUpdate = new double[vectorLength];
    while (iteration.getIterationCount() < parameter.getNumberOfIterations()) {
        iteration.alphaUpdate(vocabulary.getTotalNumberOfWords());
        wordIndex = vocabulary.getPosition((VocabularyWord*) currentSentence->getWord(iteration.getSentencePosition()));
        currentWord = vocabulary.getWord(wordIndex);
        for (int i = 0; i < vectorLength; i++){
            outputs[i] = 0;
            outputUpdate[i] = 0;
        }
        b = rand() % parameter.getWindow();
        cw = 0;
        for (int a = b; a < parameter.getWindow() * 2 + 1 - b; a++){
            int c = iteration.getSentencePosition() - parameter.getWindow() + a;
            if (a != parameter.getWindow() && currentSentence->safeIndex(c)) {
                lastWordIndex = vocabulary.getPosition((VocabularyWord*) currentSentence->getWord(c));
                for (int j = 0; j < vectorLength; j++){
                    outputs[j] += wordVectors[lastWordIndex][j];
                }
                cw++;
            }
        }
        if (cw > 0) {
            for (int j = 0; j < vectorLength; j++){
                outputs[j] /= cw;
            }
            if (parameter.isHierarchicalSoftMax()){
                for (int d = 0; d < currentWord->getCodeLength(); d++) {
                    l2 = currentWord->getPoint(d);
                    f = dotProduct(outputs, wordVectorUpdate[l2]);
                    if (f <= -MAX_EXP || f >= MAX_EXP){
                        continue;
                    } else{
                        int index = (int)((f + MAX_EXP) * (EXP_TABLE_SIZE / MAX_EXP / 2));
                        if (index >= 0 && index < EXP_TABLE_SIZE){
                            f = expTable[index];
                        } else {
                            continue;
                        }
                    }
                    g = (1 - currentWord->getCode(d) - f) * iteration.getAlpha();
                    updateOutput(outputUpdate, outputs, l2, g);
                }
            } else {
                for (int d = 0; d < parameter.getNegativeSamplingSize() + 1; d++) {
                    if (d == 0) {
                        target = wordIndex;
                        label = 1;
                    } else {
                        target = vocabulary.getTableValue(rand() % vocabulary.getTableSize());
                        if (target == 0)
                            target = rand() % (vocabulary.size() - 1) + 1;
                        if (target == wordIndex)
                            continue;
                        label = 0;
                    }
                    l2 = target;
                    f = dotProduct(outputs, wordVectorUpdate[l2]);
                    g = calculateG(f, iteration.getAlpha(), label);
                    updateOutput(outputUpdate, outputs, l2, g);
                }
            }
            for (int a = b; a < parameter.getWindow() * 2 + 1 - b; a++){
                int c = iteration.getSentencePosition() - parameter.getWindow() + a;
                if (a != parameter.getWindow() && currentSentence->safeIndex(c)) {
                    lastWordIndex = vocabulary.getPosition((VocabularyWord*) currentSentence->getWord(c));
                    for (int j = 0; j < vectorLength; j++){
                        wordVectors[lastWordIndex][j] += outputUpdate[j];
                    }
                }
            }
        }
        currentSentence = iteration.sentenceUpdate(currentSentence);
    }
    corpus->close();
}

/**
 * Main method for training the SkipGram version of Word2Vec algorithm.
 */
void NeuralNetwork::trainSkipGram() {
    int wordIndex, lastWordIndex;
    Iteration iteration = Iteration(corpus, parameter);
    int target, label, l1, l2, b;
    double f, g;
    corpus->open();
    Sentence* currentSentence = corpus->getSentence();
    VocabularyWord* currentWord;
    auto* outputUpdate = new double[vectorLength];
    while (iteration.getIterationCount() < parameter.getNumberOfIterations()) {
        iteration.alphaUpdate(vocabulary.getTotalNumberOfWords());
        wordIndex = vocabulary.getPosition((VocabularyWord*) currentSentence->getWord(iteration.getSentencePosition()));
        currentWord = vocabulary.getWord(wordIndex);
        for (int i = 0; i < vectorLength; i++){
            outputUpdate[i] = 0;
        }
        b = rand() % parameter.getWindow();
        for (int a = b; a < parameter.getWindow() * 2 + 1 - b; a++) {
            int c = iteration.getSentencePosition() - parameter.getWindow() + a;
            if (a != parameter.getWindow() && currentSentence->safeIndex(c)) {
                lastWordIndex = vocabulary.getPosition((VocabularyWord*) currentSentence->getWord(c));
                l1 = lastWordIndex;
                for (int i = 0; i < vectorLength; i++){
                    outputUpdate[i] = 0;
                }
                if (parameter.isHierarchicalSoftMax()) {
                    for (int d = 0; d < currentWord->getCodeLength(); d++) {
                        l2 = currentWord->getPoint(d);
                        f = dotProduct(wordVectors[l1], wordVectorUpdate[l2]);
                        if (f <= -MAX_EXP || f >= MAX_EXP){
                            continue;
                        } else{
                            int index = (int)((f + MAX_EXP) * (EXP_TABLE_SIZE / MAX_EXP / 2));
                            if (index >= 0 && index < EXP_TABLE_SIZE){
                                f = expTable[index];
                            } else {
                                continue;
                            }
                        }
                        g = (1 - currentWord->getCode(d) - f) * iteration.getAlpha();
                        updateOutput(outputUpdate, wordVectors[l1], l2, g);
                    }
                } else {
                    for (int d = 0; d < parameter.getNegativeSamplingSize() + 1; d++) {
                        if (d == 0) {
                            target = wordIndex;
                            label = 1;
                        } else {
                            target = vocabulary.getTableValue(rand() % vocabulary.getTableSize());
                            if (target == 0)
                                target = rand() % (vocabulary.size() - 1) + 1;
                            if (target == wordIndex)
                                continue;
                            label = 0;
                        }
                        l2 = target;
                        f = dotProduct(wordVectors[l1], wordVectorUpdate[l2]);
                        g = calculateG(f, iteration.getAlpha(), label);
                        updateOutput(outputUpdate, wordVectors[l1], l2, g);
                    }
                }
                for (int j = 0; j < vectorLength; j++){
                    wordVectors[l1][j] += outputUpdate[j];
                }
            }
        }
        currentSentence = iteration.sentenceUpdate(currentSentence);
    }
    corpus->close();
}

NeuralNetwork::~NeuralNetwork() = default;

int NeuralNetwork::vocabularySize() const {
    return vocabulary.size();
}
