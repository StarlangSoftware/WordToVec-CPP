//
// Created by Olcay Taner Yıldız on 17.02.2019.
//

#include "WordToVecParameter.h"

WordToVecParameter::WordToVecParameter() = default;

int WordToVecParameter::getLayerSize() {
    return layerSize;
}

bool WordToVecParameter::isCbow() {
    return cbow;
}

double WordToVecParameter::getAlpha() {
    return alpha;
}

int WordToVecParameter::getWindow() {
    return window;
}

bool WordToVecParameter::isHierarchicalSoftMax() {
    return hierarchicalSoftMax;
}

int WordToVecParameter::getNegativeSamplingSize() {
    return negativeSamplingSize;
}

int WordToVecParameter::getNumberOfIterations() {
    return numberOfIterations;
}

void WordToVecParameter::setLayerSize(int layerSize) {
    this->layerSize = layerSize;
}

void WordToVecParameter::setCbow(bool cbow) {
    this->cbow = cbow;
}

void WordToVecParameter::setAlpha(double alpha) {
    this->alpha = alpha;
}

void WordToVecParameter::setWindow(int window) {
    this->window = window;
}

void WordToVecParameter::setHierarchicalSoftMax(bool hierarchicalSoftMax) {
    this->hierarchicalSoftMax = hierarchicalSoftMax;
}

void WordToVecParameter::setNegativeSamplingSize(int negativeSamplingSize) {
    this->negativeSamplingSize = negativeSamplingSize;
}

void WordToVecParameter::setNumberOfIterations(int numberOfIterations) {
    this->numberOfIterations = numberOfIterations;
}
