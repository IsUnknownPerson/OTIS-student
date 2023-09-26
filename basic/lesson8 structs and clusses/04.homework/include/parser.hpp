#pragma once

#include <istream>

#include "astnode.hpp"
#include "lexer.hpp"


class Parser {
  public:
    explicit Parser(Lexer &lexer)
        : lexer_(lexer) {}

    Parser(const Parser &other) = delete;

    Parser &operator=(const Parser &other) = delete;

    ~Parser() {
        std::cout << "Parser distructor" << std::endl;

    }

    ASTNode *parse();

  private:
    void next_token();

    ASTNode *expr();

    ASTNode *term();

    ASTNode *prim();

    Lexer &lexer_;
    Lexer::Token tok_;
};
