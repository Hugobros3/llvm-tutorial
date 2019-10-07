#include <string>
#include <memory>
#include <utility>
#include <vector>

#pragma once

// Forward declarations nonsense
class ExpressionNode;

class Visitor;

class ExpressionNode {
public:
    virtual ~ExpressionNode() = default;
    virtual void accept(Visitor& v) = 0;
};

class NumberNode : public ExpressionNode {
    double value;
public:
    explicit NumberNode(double val) : value(val) {}
    void accept(Visitor &v) override;
};

class VariableNode : public ExpressionNode {
    std::string name;
public:
    explicit VariableNode(std::string &name) : name(name) {}
    void accept(Visitor &v) override;
};

class BinaryExpression : public ExpressionNode {
    char operand; //TODO no no no
    std::unique_ptr<ExpressionNode> left, right;
public:
    BinaryExpression(char operand, std::unique_ptr<ExpressionNode> left, std::unique_ptr<ExpressionNode> right)
            : operand(operand), left(std::move(left)), right(std::move(right)) {}
    void accept(Visitor &v) override;
};

class FunctionCall : public ExpressionNode {
    std::string function_name;
    std::vector<std::unique_ptr<ExpressionNode>> arguments;
public:
    FunctionCall(const std::string &functionName, std::vector<std::unique_ptr<ExpressionNode>> arguments)
            : function_name(functionName), arguments(std::move(arguments)) {}
    void accept(Visitor &v) override;
};

class Prototype {
    std::string name;
    std::vector<std::string> arguments;
public:
    Prototype(const std::string &name, std::vector<std::string> arguments) : name(name),
                                                                             arguments(std::move(arguments)) {}
};

class Function {
    std::unique_ptr<Prototype> prototype;
    std::unique_ptr<ExpressionNode> body;
public:
    Function(std::unique_ptr<Prototype> prototype, std::unique_ptr<ExpressionNode> body) : prototype(std::move(
            prototype)), body(std::move(body)) {}
};