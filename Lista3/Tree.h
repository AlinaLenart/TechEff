#ifndef TREE_H
#define TREE_H

#include <set>

#include "Node.h"
#include <string>

using namespace std;

class Tree {
private:
    Node* root;
    bool invalidInput;
    set<string> variables;

    Node* buildTreeHelper(const vector<string>& tokens, int& index);
    void printPrefixHelper(Node* node) const;
    string inorderTraversal(Node* node) const;
    double evaluateMathExpression(const string& expression) const;
    string replaceVariablesWithValues(const string& expression, const vector<double>& varValues) const;

public:
    Tree();
    ~Tree();
    void enter(const string& expression);              //todo
    void printPrefix() const;
    void buildTree(const vector<string>& tokens);
    string getInOrder() const;
    void vars() const;
    void comp(const vector<double>& varValues);
};

#endif
