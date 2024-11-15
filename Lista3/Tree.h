#ifndef TREE_H
#define TREE_H

#include <map>

#include "Node.h"
#include <string>

using namespace std;

class Tree {
private:
    Node* root;
    bool invalidInput;

    void copyChildren(Node* dest, Node* src);
    Node* buildTreeHelper(const vector<string>& tokens, int& index);
    void printPrefixHelper(Node* node) const;
    string inorderTraversal(Node* node) const;
    //double evaluateMathExpression(const string& expression) const;
    //void completeVariablesWithValues(const vector<int>& varValues);
    double compHelper(Node* node);
    Node* findLeaf(Node* node) const;
    Node* findParent(Node* root, Node* child) const;


public:
    Tree();
    ~Tree();
    Tree(const Tree& other);
    void enter(const string& expression);              //todo
    void printPrefix() const;
    void buildTree(const vector<string>& tokens);
    string getInOrder() const;
    void vars() const;
    void comp(const vector<int>& varValues);
    map<string, int> variables; //todo make private
    Tree operator+(Tree &other) const;
    Tree& operator=(const Tree& rhs);
};

#endif
