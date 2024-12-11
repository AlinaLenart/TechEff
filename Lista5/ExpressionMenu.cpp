#include "ExpressionMenu.h"
#include "Constants.h"
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <sstream>
#include "Tree.h"
#include "Error.h"
#include "ResultSaver.h"

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
        commandStream >> command;
        string expression;
        getline(commandStream >> ws, expression);

        if (command == ENTER_CMD) {
            enterExpression(expression);
        }
        else if (command == PRINT_PREFIX_CMD) {
            printPrefixExpression();
        }
        else if (command == PRINT_INFIX_CMD) {
            printInfixExpression();
        }
        else if (command == JOIN_TREES_CMD) {
            joinExpressions(expression);
        }
        else if (command == INFO_MENU_CMD) {
            displayCommands();
        }
        else if (command == EXIT_CMD) {
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

    Result<Tree*, Error> result = expressionTree.buildTree(tokens);
    if (result.bIsSuccess()) {
        cout << "SUCCESS: " << expression << endl;
        expressionTree = *result.cGetValue();
    }
    else {
        cout << "FAILURE: \n" << result.sGetErrors() << endl;
    }

    char saveChoice;
    cout << "Do you want to save the result to a file? (y/n): ";
    cin >> saveChoice;
    if (saveChoice == 'y' || saveChoice == 'Y') {
        ResultSaver<Tree*, Error>::saveToFile(result); //odpali to z tree*
    }

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

void ExpressionMenu::joinExpressions(string expression) {
    vector<string> tokens = tokenizeExpression(expression);
    Tree tree;
    Result<Tree*, Error> newTree = tree.buildTree(tokens);
    if (newTree.bIsSuccess()) {
        cout << "SUCCESS: " << expression << endl;
        tree = *newTree.cGetValue();
        cout<< "You want to join: " << expression <<" to: " << tree.printPrefix()<<endl;
        tree = expressionTree + tree;
        expressionTree = tree;
        cout<<"Expression joined correctly: "<< expressionTree.printPrefix() <<endl;
    }
    else {
        cout << "FAILURE: \n" << newTree.sGetErrors() << endl;
    }

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
    cout << "  join <prefix-expression>  - Join two expressions\n";
}

