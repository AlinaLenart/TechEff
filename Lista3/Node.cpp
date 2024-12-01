#include "Node.h"

// konstruktor dla operatora
Node::Node(const NodeType t, const string& val, const int numChildren) :
    type(t), value(val), constantValue(0), childrenAmount(numChildren) {}


//konstruktor dla zmiennej
Node::Node(const NodeType t, const string& val) :
    type(t), value(val), constantValue(0), childrenAmount(0) {}

// konstruktor dla stalej
Node::Node(int val)
    : type(CONSTANT), constantValue(val), childrenAmount(0) {
    value = std::to_string(val);
}
//konstruktor kopiujacy
Node::Node(const Node& other)
    : type(other.type), value(other.value), children() {
    //dzieci kopiuje w drzewie
}

void Node::addChild(Node* child) {
    children.push_back(child);
}

Node::~Node() {
    for (size_t i = 0; i < children.size(); ++i) {
        delete children[i];
    }
}

bool Node::isLeaf() const{
    return children.empty();
}

