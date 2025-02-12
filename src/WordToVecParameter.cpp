//
// Created by Olcay Taner Yıldız on 17.02.2019.
//

#include "WordToVecParameter.h"

/**
 * Empty constructor for Word2Vec parameter
 */
WordToVecParameter::WordToVecParameter() = default;

/**
 * Accessor for layerSize attribute.
 * @return Size of the word vectors.
 */
int WordToVecParameter::getLayerSize() const{
    return layerSize;
}

/**
 * Accessor for CBow attribute.
 * @return True is CBow will be applied, false otherwise.
 */
bool WordToVecParameter::isCbow() const{
    return cbow;
}

/**
 * Accessor for the alpha attribute.
 * @return Current learning rate alpha.
 */
double WordToVecParameter::getAlpha() const{
    return alpha;
}

/**
 * Accessor for the window size attribute.
 * @return Current window size.
 */
int WordToVecParameter::getWindow() const{
    return window;
}

/**
 * Accessor for the hierarchicalSoftMax attribute.
 * @return If hierarchical softmax will be applied, returns true; false otherwise.
 */
bool WordToVecParameter::isHierarchicalSoftMax() const{
    return hierarchicalSoftMax;
}

/**
 * Accessor for the negativeSamplingSize attribute.
 * @return Number of negative samples that will be withdrawn.
 */
int WordToVecParameter::getNegativeSamplingSize() const{
    return negativeSamplingSize;
}

/**
 * Accessor for the numberOfIterations attribute.
 * @return Number of epochs to train the network.
 */
int WordToVecParameter::getNumberOfIterations() const{
    return numberOfIterations;
}

/**
 * Accessor for the seed attribute.
 * @return Seed to train the network.
 */
int WordToVecParameter::getSeed() const{
    return seed;
}

/**
 * Mutator for the layerSize attribute.
 * @param layerSize New size of the word vectors.
 */
void WordToVecParameter::setLayerSize(int layerSize) {
    this->layerSize = layerSize;
}

/**
 * Mutator for cBow attribute
 * @param cbow True if CBow applied; false if SkipGram applied.
 */
void WordToVecParameter::setCbow(bool cbow) {
    this->cbow = cbow;
}

/**
 * Mutator for alpha attribute
 * @param alpha New learning rate.
 */
void WordToVecParameter::setAlpha(double alpha) {
    this->alpha = alpha;
}

/**
 * Mutator for the window size attribute.
 * @param window New window size.
 */
void WordToVecParameter::setWindow(int window) {
    this->window = window;
}

/**
 * Mutator for the hierarchicalSoftMax attribute.
 * @param hierarchicalSoftMax True is hierarchical softMax applied; false otherwise.
 */
void WordToVecParameter::setHierarchicalSoftMax(bool hierarchicalSoftMax) {
    this->hierarchicalSoftMax = hierarchicalSoftMax;
}

/**
 * Mutator for the negativeSamplingSize attribute.
 * @param negativeSamplingSize New number of negative instances that will be withdrawn.
 */
void WordToVecParameter::setNegativeSamplingSize(int negativeSamplingSize) {
    this->negativeSamplingSize = negativeSamplingSize;
}

/**
 * Mutator for the numberOfIterations attribute.
 * @param numberOfIterations New number of iterations.
 */
void WordToVecParameter::setNumberOfIterations(int numberOfIterations) {
    this->numberOfIterations = numberOfIterations;
}

/**
 * Mutator for the seed attribute.
 * @param seed New number of seed.
 */
void WordToVecParameter::setSeed(int seed) {
    this->seed = seed;
}