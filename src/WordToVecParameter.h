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
    int numberOfIterations = 2;
    int seed = 1;
public:
    WordToVecParameter();
    [[nodiscard]] int getLayerSize() const;
    [[nodiscard]] bool isCbow() const;
    [[nodiscard]] double getAlpha() const;
    [[nodiscard]] int getWindow() const;
    [[nodiscard]] bool isHierarchicalSoftMax() const;
    [[nodiscard]] int getNegativeSamplingSize() const;
    [[nodiscard]] int getNumberOfIterations() const;
    [[nodiscard]] int getSeed() const;
    void setLayerSize(int _layerSize);
    void setCbow(bool _cbow);
    void setAlpha(double _alpha);
    void setWindow(int _window);
    void setHierarchicalSoftMax(bool _hierarchicalSoftMax);
    void setNegativeSamplingSize(int _negativeSamplingSize);
    void setNumberOfIterations(int _numberOfIterations);
    void setSeed(int _seed);
};


#endif //WORDTOVEC_WORDTOVECPARAMETER_H
