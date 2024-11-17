
#ifndef EXPRESSIONREADER_H
#define EXPRESSIONREADER_H
#include "Tree.h"

using namespace std;

class ExpressionReader {
public:
    ExpressionReader();
    void startMenu();

private:
    Tree expressionTree;
    void enterExpression(string expression);
    void printPrefixExpression() const;
    void printInfixExpression() const;
    void showVariables() const;
    void computeExpression(string expression);
    void joinExpressions(string expression);

    vector<string> tokenizeExpression(const string& expr);
    vector<int> tokenizeIntExpression(const string& expr);
};


#endif //EXPRESSIONREADER_H
