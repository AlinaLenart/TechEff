#ifndef TREE_H
#define TREE_H

#include <map>
#include "Node.h"
#include <string>

using namespace std;

class Tree {
public:
    Tree();
    ~Tree();
    Tree(const Tree& other);

    Node* getRoot() const;
    map<string, int> getVariables() const;

    string printPrefix() const;
    void buildTree(const vector<string>& tokens);
    string getInOrder() const;
    void vars() const;
    void comp(const vector<int>& varValues);
    Tree operator+(Tree &other) const;
    Tree& operator=(const Tree& rhs);
    int countGreatherThan(int number) const;


private:
    Node* root;
    map<string, int> variables;

    void copyChildren(Node* dest, Node* src);
    Node* buildTreeHelper(const vector<string>& tokens, int& index);
    string printPrefixHelper(Node* node) const;
    string inorderTraversal(Node* node) const;
    double compHelper(Node* node);
    Node* findLeaf(Node* node) const;
    Node* findParent(Node* root, Node* child) const;
    Node* copySubtree(Node* node) const;
    void replaceChild(Node* parentNode, Node* oldChild, Node* newChild) const;
    void swap(Tree& other);
    string intToString(int value);
    void countGreatherThanHelper(int &count, int number, Node *node) const;

};

#endif