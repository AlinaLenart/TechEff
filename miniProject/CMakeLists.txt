cmake_minimum_required(VERSION 3.29)
project(mini_project2)

set(CMAKE_CXX_STANDARD 14)

add_executable(mini_project2
        GaussianGroupingEvaluatorFactory.cpp
        GaussianGroupingEvaluatorFactory.h
        GroupingChallenge.cpp
        GroupingEvaluator.cpp
        GroupingEvaluator.h
        Optimizer.cpp
        Optimizer.h
        Point.cpp
        Point.h)
