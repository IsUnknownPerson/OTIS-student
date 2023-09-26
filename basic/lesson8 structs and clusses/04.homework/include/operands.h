#pragma once

#include "astnode.hpp"


class Add: public ASTNode {
public:
    inline Add(ASTNode *lhs, ASTNode *rhs) :
        ASTNode("+", lhs, rhs) {}
    ~Add() override
    {
       std::cout << "Add distructor" << std::endl;
    }
};


class Sub: public ASTNode {
public:
    inline Sub(ASTNode *lhs, ASTNode *rhs) :
        ASTNode("-", lhs, rhs) {}
};


class Mul: public ASTNode {
public:
    inline Mul(ASTNode *lhs, ASTNode *rhs) :
        ASTNode("*", lhs, rhs) {}
};


class Div: public ASTNode {
public:
    inline Div(ASTNode *lhs, ASTNode *rhs) :
        ASTNode("/", lhs, rhs) {}
};


class LBrace: public ASTNode {
public:
    inline LBrace(ASTNode *lhs, ASTNode *rhs) :
        ASTNode("(", lhs, rhs) {}
};

class RBrace: public ASTNode {
public:
    inline RBrace(ASTNode *lhs, ASTNode *rhs) :
        ASTNode("", lhs, rhs) {}
    //1+2*(3+4+6)-5
};





