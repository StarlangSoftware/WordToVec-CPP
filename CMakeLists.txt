cmake_minimum_required(VERSION 3.12)
project(WordToVec)

set(CMAKE_CXX_STANDARD 20)

include_directories(include)
link_directories(library)

add_library(WordToVec VocabularyWord.cpp VocabularyWord.h WordToVecParameter.cpp WordToVecParameter.h Vocabulary.cpp Vocabulary.h NeuralNetwork.cpp NeuralNetwork.h Iteration.cpp Iteration.h)

target_link_libraries(WordToVec Dictionary Corpus Math)

add_executable(Test VocabularyWord.cpp VocabularyWord.h WordToVecParameter.cpp WordToVecParameter.h Vocabulary.cpp Vocabulary.h NeuralNetwork.cpp NeuralNetwork.h Iteration.cpp Iteration.h Test/NeuralNetworkTest.cpp)

target_link_libraries(Test Dictionary Corpus Math)

