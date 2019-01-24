#include "pch.h"
#include "Node.h"

Node::Node(int value)
{
    Node::value = value;
    next = nullptr;
}

Node::~Node()
{
}