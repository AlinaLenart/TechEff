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
    map<string, int> variables; //todo make private

    void copyChildren(Node* dest, Node* src);
    Node* buildTreeHelper(const vector<string>& tokens, int& index);
    void printPrefixHelper(Node* node) const;
    string inorderTraversal(Node* node) const;
    //double evaluateMathExpression(const string& expression) const;
    //void completeVariablesWithValues(const vector<int>& varValues);
    double compHelper(Node* node);
    Node* findLeaf(Node* node) const;
    Node* findParent(Node* root, Node* child) const;
    Node* copySubtree(Node* node) const;
    void replaceChild(Node* parentNode, Node* oldChild, Node* newChild) const;
    void swap(Tree& other);


public:
    Tree();
    ~Tree();
    Tree(const Tree& other);

    Node* getRoot() const;
    map<string, int> getVariables() const;

    void printPrefix() const;
    void buildTree(const vector<string>& tokens);
    string getInOrder() const;
    void vars() const;
    void comp(const vector<int>& varValues);
    Tree operator+(Tree &other) const;
    Tree& operator=(const Tree& rhs);
};

#endif
