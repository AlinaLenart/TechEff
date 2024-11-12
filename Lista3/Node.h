#ifndef NODE_H
#define NODE_H

#include <string>
#include <vector>

using namespace std;

enum NodeType { OPERATOR, VARIABLE, CONSTANT };

class Node {
public:
    NodeType type;
    string value;
    int constantValue;
    vector<Node*> children;
    int childrenAmount;

    Node(NodeType t, const string& val, int numChildren);
    Node(NodeType t, const string& val);
    explicit Node(int val);
    ~Node();
    void addChild(Node* child);
};

#endif
