#include "parser.h"
#include "tokens.h"

#include <map>

int current_token;

int get_next_token() {
    return current_token = get_token();
}

std::unique_ptr<ExpressionNode> parse_expression();

std::unique_ptr<ExpressionNode> die(const char *prout) {
    return nullptr;
}

std::unique_ptr<ExpressionNode> parse_number_expression() {
    auto result = std::make_unique<NumberNode>(getNumberValue());
    get_next_token();
    return std::move(result);
}

std::unique_ptr<ExpressionNode> parse_parentheses_expression() {
    get_next_token();
    auto v = parse_expression();
    if (current_token != ')')
        return die("Expected ')'");

    get_next_token();
    return v;
}

std::unique_ptr<ExpressionNode> parse_identifier_expr() {
    std::string identifier_name = getIdentifierString();
    get_next_token();

    if (current_token != '(')
        return std::make_unique<VariableNode>(identifier_name);

    get_next_token();
    std::vector<std::unique_ptr<ExpressionNode>> args;
    if (current_token != ')') {
        while (true) {
            if (auto arg = parse_expression()) {
                args.push_back(std::move(arg));
            } else {
                die("failed to parse argument");
            }

            if (current_token == ')')
                break;

            if (current_token != ',') {
                die("expected ',' | ')");
            }

            get_next_token();
        }
    }

    get_next_token(); // eat )

    return std::make_unique<FunctionCall>(identifier_name, std::move(args));
}

std::unique_ptr<ExpressionNode> parse_primary() {
    switch (current_token) {
        default:
            return die("unknown token");
        case TOKEN_IDENTIFIER:
            return parse_identifier_expr();
        case TOKEN_NUMBER:
            return parse_number_expression();
        case '(':
            return parse_parentheses_expression();
    }
}

const std::map<char, int> operator_precedence = {
        {'<', 10},
        {'+', 20},
        {'-', 20},
        {'*', 40},
};

int get_precedence(int token) {
    if (!isascii(token))
        return -1;

    int precedence = operator_precedence.at(token);
    if (precedence <= 0) return -1;
    return precedence;
}

std::unique_ptr<ExpressionNode> parse_binop_rhs(int prev_precedence, std::unique_ptr<ExpressionNode> left) {
    while(true) {
        int token_precedence = get_precedence(current_token);

        if(token_precedence < prev_precedence)
            return left;

        // we can infer it's a binop (prec > 0)
        int binop = current_token;
        get_next_token();

        auto right = parse_primary();

        int next_precedence = get_precedence(current_token);
        if (token_precedence < next_precedence) {
            right = parse_binop_rhs(token_precedence + 1, std::move(right));
        }

        left = std::make_unique<BinaryExpression>(binop, std::move(left), std::move(right));
    }
}

std::unique_ptr<ExpressionNode> parse_expression() {
    auto left = parse_primary();

    return parse_binop_rhs(0, std::move(left));
}

std::unique_ptr<Prototype> parse_prototype() {
    if (current_token != TOKEN_IDENTIFIER) {
        die("Expected fn name");
    }

    std::string function_name = getIdentifierString();
    get_next_token();

    if(current_token != '(')
        die("Expected (");

    std::vector<std::string> argument_names;
    while(get_next_token() == TOKEN_IDENTIFIER) {
        argument_names.push_back(getIdentifierString());
    }

    if(current_token != ')')
        die("Expected )");

    get_next_token();

    return std::make_unique<Prototype>(function_name, std::move(argument_names));
}

std::unique_ptr<Function> parse_function_definition() {
    get_next_token();
    auto prototype = parse_prototype();
    auto expression = parse_expression();

    return std::make_unique<Function>(std::move(prototype), std::move(expression));
}

std::unique_ptr<Function> parse_top_level() {
    auto expression = parse_expression();
    auto prototype = std::make_unique<Prototype>("", std::vector<std::string>());
    return std::make_unique<Function>(std::move(prototype), std::move(expression));
}