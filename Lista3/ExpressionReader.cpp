#include "ExpressionReader.h"
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <sstream>
#include "Tree.h"

using namespace std;

ExpressionReader::ExpressionReader() : expressionTree() {}

void ExpressionReader::startMenu() {
    string input;
    cout << "\n--- Command Menu ---\n";
    cout << "Commands:\n";
    cout << "  enter <prefix-expression> - Enter a prefix expression\n";
    cout << "  print-prefix              - Print the prefix expression\n";
    cout << "  print-infix               - Print the infix expression\n";
    cout << "  vars                      - Show all variables\n";
    cout << "  compute                   - Compute the expression\n";
    cout << "  join <prefix-expression>  - Join two expressions\n";
    cout << "  exit                      - Exit the program\n";

    bool exit = false;
    while (!exit) {
        cout << "\nType your command: ";
        getline(cin >> ws, input);
        istringstream commandStream(input);
        string command;
        commandStream >> command; // pierwszy wyraz
        string expression;
        getline(commandStream >> ws, expression);//reszta

        if (command == "enter") {
            enterExpression(expression);
        }
        else if (command == "print-prefix") {
            printPrefixExpression();
        }
        else if (command == "print-infix") {
            printInfixExpression();
        }
        else if (command == "vars") {
            showVariables();
        }
        else if (command == "comp") {
            computeExpression(expression);
        }
        else if (command == "join") {
            joinExpressions(expression);
        }
        else if (command == "exit") {
            cout << "Exiting...\n";
            exit = true;
        }
        else {
            cout << "Invalid command. Please try again\n";
        }
    }
}

//todo moze przydaloby sie getRoot == nullptr to nic nie rob

void ExpressionReader::enterExpression(string expression) {
    vector<string> tokens = tokenizeExpression(expression);
    cout << "Expression entered: " << expression << endl;

    expressionTree.buildTree(tokens);
}

void ExpressionReader::printPrefixExpression() const {
    //if(expressionTree.)
    cout << "Prefix Expression: ";
    expressionTree.printPrefix();
}

void ExpressionReader::printInfixExpression() const {
    cout << "Infix Expression: " << expressionTree.getInOrder() << endl;
}//todo nazwa funkcji getinorder meh

void ExpressionReader::showVariables() const {
    cout << "Variables in expression: ";
    expressionTree.vars();
}

void ExpressionReader::computeExpression(string expression) {
    vector<int> varValues = tokenizeIntExpression(expression);

    if (varValues.size() != expressionTree.getVariables().size()) {
        cout << "ERROR: Number of values provided (" << varValues.size()
                  << ") does not match the number of variables (" << expressionTree.getVariables().size() << ").\n";
        return;
    }
    std::cout << "Extracted numbers:" << std::endl;
    for (size_t i = 0; i < varValues.size(); ++i) {
        std::cout << varValues[i] << "; ";
    }
    std::cout << std::endl;

    expressionTree.comp(varValues);
}

void ExpressionReader::joinExpressions(string expression) {
    vector<string> tokens = tokenizeExpression(expression);
    Tree tree;
    tree.buildTree(tokens);
    cout<< "You want to join: " << expression;
    cout<<" to: ";
    expressionTree.printPrefix();
    tree = expressionTree + tree;
    expressionTree = tree;
    cout<<"Expression joined correctly: ";
    expressionTree.printPrefix();
}

vector<string> ExpressionReader::tokenizeExpression(const string& expr) {
    vector<string> tokens;
    stringstream ss(expr);
    string token;

    while (ss >> token) {
        tokens.push_back(token);
    }

    return tokens;
}

vector<int> ExpressionReader::tokenizeIntExpression(const string& expr) {
    vector<int> tokens;
    stringstream ss(expr);
    string token;

    while (ss >> token) {
        stringstream tokenStream(token);
        int number;
        tokenStream >> number;

        if (tokenStream.fail()) {
            cerr << "Invalid number: " << token << endl;
        } else {
            tokens.push_back(number);
        }
    }

    return tokens;
}


