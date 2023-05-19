#include "parser.hpp"
#include "number.hpp"
#include "operands.h"
#include "name.h"

using Token = Lexer::Token;

ASTNode *Parser::parse() { return expr(); }

void Parser::next_token() { tok_ = lexer_.next_token(); }

//term считывает и вычисляет первое слагаемое, функция get_token считывает знак операции

ASTNode *Parser::expr() {
    // parse addition and subsctruction
    //есть ли скобка
    ASTNode *root = term(); //число или умножение или деление
    for (;;) {
        switch (tok_)
        {
        case Token::Operator: {
            std::string op = lexer_.get_operator();
            switch (op.front())
            {
            case '+':
            {
                // Implement Add class and uncomment this line
                //auto temp = term();
                root = new Add(root, term());
                break;
            }

            case '-':
                // Implement Sub class and uncomment this line
                root = new Sub(root, term());
                break;
            default:
                return root;
            }
            break;
        }
        default:
            return root;
        }
    }
}

ASTNode *Parser::term() {
    // parse multiplication and division
    ASTNode *root = prim();
    for (;;) {
        switch (tok_) {
        case Token::Operator: {
            std::string op = lexer_.get_operator();
            switch (op.front()) {
            case '*':
                // Implement Mul class and uncomment this line
                root = new Mul(root, prim());
                //return nullptr;
                break;
            case '/':
                // Implement Div class and uncomment this line
                root = new Div(root, prim());
                //return nullptr;
                break;
            default:
                return root;
            }
            break;
        }
        default:

            if (tok_ != Token::End)
            {
                std::cout << "Error. Incorrect input" << std::endl;
            }

            /*
            if (tok_ == Token::Number)
                std::cout << "token == Number" << std::endl;
            else if (tok_ == Token::Operator)
                std::cout << "token == Operator" << std::endl;
            else if (tok_ == Token::End)
                std::cout << "token == End" << std::endl;
            else if (tok_ == Token::Lbrace)
                std::cout << "token == Lbrace" << std::endl;
            else if (tok_ == Token::Rbrace)
                std::cout << "token == Rbrace" << std::endl;
            else if (tok_ == Token::Name)
                std::cout << "token == Name" << std::endl;
            else
                std::cout << "unknown token" << std::endl;

            std::cout << "get_operator default: " << lexer_.get_operator() << std::endl;
            std::cout << "get_operator default front: " << lexer_.get_operator() << std::endl;
            std::cout << "get_name default: " << lexer_.get_name() << std::endl;
            std::cout << "get_name default front: " << lexer_.get_name() << std::endl;
            std::cout << "get_number default: " << lexer_.get_number() << std::endl;
            std::cout << "get_number default front: " << lexer_.get_number() << std::endl;
            */
           return root;
        }
    }
}

ASTNode *Parser::prim() {
    // parse numbers and names
    ASTNode *node = nullptr;
    next_token();
    switch (tok_) {
    case Token::Number:
        node = new Number(lexer_.get_number());
        break;
    case Token::Name:
        // Implement Variable class and uncomment this line
        node = new Variable(lexer_.get_name());
        //return nullptr;
        break;
    case Token::Lbrace:
        //std::cout << " We are here on Lbrace " << std::endl;
        node = new LBrace(node, expr());
        //next_token();
        break;

    case Token::Rbrace:
        //std::cout << " We are here on Rbrace " << std::endl;
        //node = new RBrace(prim(), node);
        //next_token();
        break;
    default:
        break;
    }
    next_token();
    return node;
}

