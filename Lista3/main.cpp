#include <iostream>
#include <string>
#include <vector>

#include "ExpressionReader.h"
#include "Tree.h"

int main() {
    ExpressionReader reader;
    reader.startMenu();








    // std::string expression1("* + a b c");
    // std::string expression2 = "+ * 5 sin x * + a b 8";
    // std::string expression3 = "+ + + 2 3";
    //
    // Tree tree1;
    // Tree tree2;
    // Tree tree3;
    // Tree tree4;
    //
    // std::vector<std::string> tokens1;
    // tokens1.push_back("*");
    // tokens1.push_back("+");
    // tokens1.push_back("a");
    // tokens1.push_back("b");
    // tokens1.push_back("c");
    //
    // std::vector<std::string> tokens2;
    // tokens2.push_back("+");
    // tokens2.push_back("*");
    // tokens2.push_back("5");
    // tokens2.push_back("sin");
    // tokens2.push_back("x");
    // tokens2.push_back("*");
    // tokens2.push_back("+");
    // tokens2.push_back("a");
    // tokens2.push_back("b");
    // tokens2.push_back("8");
    //
    // std::vector<std::string> tokens3;
    // tokens3.push_back("+");
    // tokens3.push_back("+");
    // tokens3.push_back("+");
    // tokens3.push_back("2");
    // tokens3.push_back("3");
    //
    // std::vector<std::string> tokens4;
    // tokens4.push_back("*");
    // tokens4.push_back("a");
    // tokens4.push_back("b");
    //
    // tree1.buildTree(tokens1);
    // tree2.buildTree(tokens2);
    // tree3.buildTree(tokens3);
    // tree4.buildTree(tokens4);
    //
    // std::cout << "Tree 1 (prefix notation): ";
    // tree1.printPrefix();
    // cout << "Tree 1 (infix notation): " << tree1.getInOrder()<<endl;
    // tree1.vars();
    //
    // std::cout << "Tree 2 (prefix notation): ";
    // tree2.printPrefix();
    // cout << "Tree 2 (infix notation): " << tree2.getInOrder()<<endl;
    // tree2.vars();
    //
    // std::cout << "Tree 3 (prefix notation): ";
    // tree3.printPrefix();
    // cout << "Tree 3 (infix notation): " << tree3.getInOrder()<<endl;
    // tree3.vars();
    //
    // std::vector<int> values1;
    // values1.push_back(3);  // a = 3
    // values1.push_back(4);  // b = 4
    // values1.push_back(5);  // c = 5
    // std::cout << "Evaluating Tree 1 with a=3, b=4, c=5:\n";
    // tree1.comp(values1);
    // std::vector<int> values2;
    // std::cout << "Evaluating Tree 2 with a=2, b=4, x=90:\n";
    // values2.push_back(2);  // a = 2
    // values2.push_back(4);  // b = 4
    // values2.push_back(90);  // x = 90
    // tree2.comp(values2);
    //
    // Tree treeAdding = tree1 + tree4;
    // treeAdding.printPrefix();
    // cout << "Tree Added (infix notation): " << treeAdding.getInOrder()<<endl;
    //
    // std::vector<int> values3;
    // std::cout << "Evaluating Tree Adding with a=2, b=3, c=4:\n";
    // values3.push_back(2);  // a = 2
    // values3.push_back(3);  // b = 3
    // values3.push_back(4);  // x = 4
    // treeAdding.comp(values3);
    // tree1.printPrefix();
    // tree4.printPrefix();

    return 0;
}
