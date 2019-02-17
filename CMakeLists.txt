cmake_minimum_required(VERSION 3.12)
project(WordToVec)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)
link_directories(library)

add_library(WordToVec VocabularyWord.cpp VocabularyWord.h WordToVecParameter.cpp WordToVecParameter.h Vocabulary.cpp Vocabulary.h)

target_link_libraries(WordToVec Dictionary Corpus)
