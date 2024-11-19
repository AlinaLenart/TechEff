#include "ExpressionMenu.h"
#include "Constants.h"
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <sstream>
#include "Tree.h"

using namespace std;

ExpressionMenu::ExpressionMenu() : expressionTree() {}

void ExpressionMenu::startMenu() {
    string input;
    displayCommands();

    bool exit = false;
    while (!exit) {
        cout << "Type your command: ";
        getline(cin >> ws, input);
        istringstream commandStream(input);
        string command;
        commandStream >> command; // pierwszy wyraz
        string expression;
        getline(commandStream >> ws, expression);//reszta

        if (command == ENTER_COMMAND) {
            enterExpression(expression);
        }
        else if (command == PRINT_PREFIX_COMMAND) {
            printPrefixExpression();
        }
        else if (command == PRINT_INFIX_COMMAND) {
            printInfixExpression();
        }
        else if (command == VARS_COMMAND) {
            showVariables();
        }
        else if (command == COMP_COMMAND) {
            computeExpression(expression);
        }
        else if (command == JOIN_COMMAND) {
            joinExpressions(expression);
        }
        else if (command == CNTGT_COMMAND) {
            cntgtExpression(expression);
        }
        else if (command == HELP_COMMAND) {
            displayCommands();
        }
        else if (command == EXIT_COMMAND) {
            cout << "Exiting...\n";
            exit = true;
        }
        else {
            cout << "Invalid command. Please try again\n";
        }
    }
}

void ExpressionMenu::enterExpression(string expression) {
    vector<string> tokens = tokenizeExpression(expression);

    cout << "Expression entered: " << expression << endl;

    expressionTree.buildTree(tokens);
}

void ExpressionMenu::printPrefixExpression() const {
    if (!expressionTree.getRoot()) {
        cout << "First entry expression using 'enter' command " << endl;
        return;
    }
    cout << "Prefix Expression: " << expressionTree.printPrefix() << endl;;
}

void ExpressionMenu::printInfixExpression() const {
    if (!expressionTree.getRoot()) {
        cout << "First entry expression using 'enter' command " << endl;
        return;
    }
    cout << "Infix Expression: " << expressionTree.getInOrder() << endl;
}

void ExpressionMenu::showVariables() const {
    if (!expressionTree.getRoot()) {
        cout << "First entry expression using 'enter' command " << endl;
        return;
    }
    cout << "Variables in expression: ";
    expressionTree.vars();
}

void ExpressionMenu::computeExpression(string expression) {
    if (!expressionTree.getRoot()) {
        cout << "First entry expression using 'enter' commands " << endl;
        return;
    }
    vector<int> varValues = tokenizeIntExpression(expression);

    if (varValues.size() != expressionTree.getVariables().size()) {
        cout << "ERROR: Number of values provided (" << varValues.size()
                  << ") does not match the number of variables (" << expressionTree.getVariables().size() << ").\n";
        return;
    }
    cout << "Input numbers:";
    for (size_t i = 0; i < varValues.size(); ++i) {
        cout << varValues[i] << "; ";
    }
    cout << endl;

    expressionTree.comp(varValues);
}

void ExpressionMenu::joinExpressions(string expression) {
    vector<string> tokens = tokenizeExpression(expression);
    Tree tree;
    tree.buildTree(tokens);
    cout<< "You want to join: " << expression <<" to: " << tree.printPrefix()<<endl;
    tree = expressionTree + tree;
    expressionTree = tree;
    cout<<"Expression joined correctly: "<< expressionTree.printPrefix() <<endl;
}

void ExpressionMenu::cntgtExpression(string expression) {
    int number = stoi(expression);
    cout << "Counter for greather than: " << number <<" is: "<<expressionTree.countGreatherThan(number)<< endl;

}

vector<string> ExpressionMenu::tokenizeExpression(const string& expr) {
    vector<string> tokens;
    stringstream ss(expr);
    string token;

    while (ss >> token) {
        tokens.push_back(token);
    }

    return tokens;
}

vector<int> ExpressionMenu::tokenizeIntExpression(const string& expr) {
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

void ExpressionMenu::displayCommands() {
    cout << "Commands:\n";
    cout << "  enter <prefix-expression> - Enter a prefix expression\n";
    cout << "  print-prefix              - Print the prefix expression\n";
    cout << "  print-infix               - Print the infix expression\n";
    cout << "  vars                      - Show all variables\n";
    cout << "  compute                   - Compute the expression\n";
    cout << "  join <prefix-expression>  - Join two expressions\n";
    cout << "  cntgt <number>            - Count greather than\n";
}

