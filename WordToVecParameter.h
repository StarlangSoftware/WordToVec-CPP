//
// Created by Olcay Taner Yıldız on 17.02.2019.
//

#ifndef WORDTOVEC_WORDTOVECPARAMETER_H
#define WORDTOVEC_WORDTOVECPARAMETER_H


class WordToVecParameter {
private:
    int layerSize = 100;
    bool cbow = true;
    double alpha = 0.025;
    int window = 5;
    bool hierarchicalSoftMax = false;
    int negativeSamplingSize = 5;
    int numberOfIterations = 3;
public:
    WordToVecParameter();
    int getLayerSize();
    bool isCbow();
    double getAlpha();
    int getWindow();
    bool isHierarchicalSoftMax();
    int getNegativeSamplingSize();
    int getNumberOfIterations();
    void setLayerSize(int layerSize);
    void setCbow(bool cbow);
    void setAlpha(double alpha);
    void setWindow(int window);
    void setHierarchicalSoftMax(bool hierarchicalSoftMax);
    void setNegativeSamplingSize(int negativeSamplingSize);
    void setNumberOfIterations(int numberOfIterations);
};


#endif //WORDTOVEC_WORDTOVECPARAMETER_H
