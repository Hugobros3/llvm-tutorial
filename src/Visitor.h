//
// Created by hugo on 7/10/19.
//

#ifndef LLVM_TUTORIAL_VISITOR_H
#define LLVM_TUTORIAL_VISITOR_H

#include "parser.h"

class Visitor {
    /*virtual void visit(ExpressionNode& node) {

    }*/
public:
    virtual void visit(NumberNode& node) = 0;
    virtual void visit(VariableNode& node) = 0;
    virtual void visit(BinaryExpression& node) = 0;
    virtual void visit(FunctionCall& node) = 0;
};


#endif //LLVM_TUTORIAL_VISITOR_H
