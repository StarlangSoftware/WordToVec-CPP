cmake_minimum_required(VERSION 3.12)
project(WordToVec)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "-O3")

find_package(corpus REQUIRED)

add_library(WordToVec VocabularyWord.cpp VocabularyWord.h WordToVecParameter.cpp WordToVecParameter.h Vocabulary.cpp Vocabulary.h NeuralNetwork.cpp NeuralNetwork.h Iteration.cpp Iteration.h WordPair.cpp WordPair.h SemanticDataSet.cpp SemanticDataSet.h)
target_link_libraries(WordToVec corpus::corpus)
