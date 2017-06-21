cmake_minimum_required(VERSION 3.7)
project(Game)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        item.h
        List.cpp
        list.h
        personaggiGiocabili.h ItemsGenerator.cpp PGGenerator.cpp)

add_executable(Game ${SOURCE_FILES} ItemsGenerator.cpp PGGenerator.cpp)