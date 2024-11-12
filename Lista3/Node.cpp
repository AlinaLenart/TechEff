#include "Node.h"

// Konstruktor dla operatora
Node::Node(const NodeType t, const string& val, const int numChildren) :
    type(t), value(val), constantValue(0), childrenAmount(numChildren) {}


//konstruktor dla zmiennej
Node::Node(const NodeType t, const string& val) :
    type(t), value(val), constantValue(0), childrenAmount(0) {}

// Konstruktor dla stałej liczby
Node::Node(int val)
    : type(NodeType::CONSTANT), constantValue(val), childrenAmount(0) {
    value = std::to_string(val);
}

void Node::addChild(Node* child) {
    children.push_back(child);
}
Node::~Node() {
    for (size_t i = 0; i < children.size(); ++i) {
        delete children[i];
    }
}
