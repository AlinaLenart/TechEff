cmake_minimum_required(VERSION 3.29)
project(TEP_CLion)

set(CMAKE_CXX_STANDARD 98)

add_executable(TEP_CLion main.cpp
        Tree.cpp
        Node.cpp
        Node.h
        Tree.h
        Constants.h
        ExpressionMenu.cpp
        ExpressionMenu.h
)
