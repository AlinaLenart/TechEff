#ifndef EXPRESSIONREADER_H
#define EXPRESSIONREADER_H

#include "Tree.h"

using namespace std;

class ExpressionMenu {
public:
    ExpressionMenu();
    void startMenu();

private:
    Tree expressionTree;

    void enterExpression(string expression);
    void printPrefixExpression() const;
    void printInfixExpression() const;
    void joinExpressions(string expression);
    static void displayCommands();
    vector<string> tokenizeExpression(const string& expr);
    vector<int> tokenizeIntExpression(const string& expr);
};


#endif //EXPRESSIONREADER_H
