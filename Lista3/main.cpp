#include <iostream>
#include <string>
#include <vector>
#include "Tree.h"

int main() {
    // Example of a valid expression in C++98
    std::string expression1("* + a b c");  // This is a simple prefix expression
    std::string expression2 = "+ * 5 sin x * + a b 8"; // Another example expression
    std::string expression3 = "+ + + 2 3"; // Another example expression

    Tree tree1;  // Creating an instance of Tree
    Tree tree2;  // Another Tree instance
    Tree tree3;  // Another Tree instance

    // Tokenize the expressions manually for C++98 compatibility
    std::vector<std::string> tokens1;
    tokens1.push_back("*");
    tokens1.push_back("+");
    tokens1.push_back("a");
    tokens1.push_back("b");
    tokens1.push_back("c");

    std::vector<std::string> tokens2;
    tokens2.push_back("+");
    tokens2.push_back("*");
    tokens2.push_back("5");
    tokens2.push_back("sin");
    tokens2.push_back("x");
    tokens2.push_back("*");
    tokens2.push_back("+");
    tokens2.push_back("a");
    tokens2.push_back("b");
    tokens2.push_back("8");

    std::vector<std::string> tokens3;
    tokens3.push_back("+");
    tokens3.push_back("+");
    tokens3.push_back("+");
    tokens3.push_back("2");
    tokens3.push_back("3");

    // Build trees for both expressions
    tree1.buildTree(tokens1);
    tree2.buildTree(tokens2);
    tree3.buildTree(tokens3);

    // Print the tree in prefix notation (example)
    std::cout << "Tree 1 (prefix notation): ";
    tree1.printPrefix();
    cout << "Tree 1 (infix notation): " << tree1.getInOrder()<<endl;
    tree1.vars();

    std::cout << "Tree 2 (prefix notation): ";
    tree2.printPrefix();
    cout << "Tree 2 (infix notation): " << tree2.getInOrder()<<endl;
    tree2.vars();

    std::cout << "Tree 3 (prefix notation): ";
    tree3.printPrefix();
    cout << "Tree 3 (infix notation): " << tree3.getInOrder()<<endl;
    tree3.vars();


    return 0;
}
