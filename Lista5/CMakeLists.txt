cmake_minimum_required(VERSION 3.29)
project(Lista5)

set(CMAKE_CXX_STANDARD 98)

add_executable(Lista5 Main.cpp
        MySmartPointer.h
        Error.cpp
        Error.h
        Constants.h
        ExpressionMenu.cpp
        ExpressionMenu.h
        MySmartPointer.h
        Node.cpp
        Node.h
        Result.h
        ResultSaver.h
        Tree.cpp
        Tree.h
)
