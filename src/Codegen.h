//
// Created by hugo on 6/10/19.
//

#ifndef LLVM_TUTORIAL_CODEGEN_H
#define LLVM_TUTORIAL_CODEGEN_H

#include "llvm/IR/Value.h"

using namespace llvm;

#include "Visitor.h"

class Codegen: public Visitor {
    Value codegen();

public:
    void visit(NumberNode &node) override;

    void visit(VariableNode &node) override;

    void visit(BinaryExpression &node) override;

    void visit(FunctionCall &node) override;
};


#endif //LLVM_TUTORIAL_CODEGEN_H
