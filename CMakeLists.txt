cmake_minimum_required(VERSION 3.12)
project(WordToVec)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "-O3")

find_package(corpus REQUIRED)

add_library(WordToVec src/VocabularyWord.cpp src/VocabularyWord.h src/WordToVecParameter.cpp src/WordToVecParameter.h src/Vocabulary.cpp src/Vocabulary.h src/NeuralNetwork.cpp src/NeuralNetwork.h src/Iteration.cpp src/Iteration.h src/WordPair.cpp src/WordPair.h src/SemanticDataSet.cpp src/SemanticDataSet.h)
target_link_libraries(WordToVec corpus::corpus)
add_executable(Test src/VocabularyWord.cpp src/VocabularyWord.h src/WordToVecParameter.cpp src/WordToVecParameter.h src/Vocabulary.cpp src/Vocabulary.h src/NeuralNetwork.cpp src/NeuralNetwork.h src/Iteration.cpp src/Iteration.h Test/NeuralNetworkTest.cpp src/WordPair.cpp src/WordPair.h src/SemanticDataSet.cpp src/SemanticDataSet.h Test/SemanticDataSetTest.cpp)
target_link_libraries(Test corpus::corpus)
