//
// Created by hugo on 7/10/19.
//

#include "Visitor.h"

void NumberNode::accept(Visitor &v) {
    v.visit(*this);
}

void VariableNode::accept(Visitor &v) {
    v.visit(*this);
}

void BinaryExpression::accept(Visitor &v) {
    v.visit(*this);
}

void FunctionCall::accept(Visitor &v) {
    v.visit(*this);
}