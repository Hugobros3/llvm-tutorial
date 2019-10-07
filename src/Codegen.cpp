//
// Created by hugo on 6/10/19.
//

#include "Codegen.h"

#include "llvm/ADT/APFloat.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/IRBuilder.h"

using namespace llvm;

void codegen() {
    LLVMContext context;
}

void * die_(const char *death_msg) {
    printf("%s", death_msg);
    return nullptr;
}

static LLVMContext the_context;
static IRBuilder<> builder(the_context);
// owns memory for values*
static std::unique_ptr<Module> the_module;
static std::map<std::string, Value*> named_values;

Value* codegen(const NumberNode& node) {
    return ConstantFP::get(the_context, APFloat(node.value));
}

Value* codegen(const VariableNode& node) {
    auto* v = named_values[node.name];
    if(!v)
        die_("couldn't find named variable");
    return v;
}

Value Codegen::codegen() {
    throw 0;
}

void Codegen::visit(NumberNode &node) {

}

void Codegen::visit(VariableNode &node) {

}

void Codegen::visit(BinaryExpression &node) {

}

void Codegen::visit(FunctionCall &node) {

}
