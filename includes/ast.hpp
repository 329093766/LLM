#ifndef __AST_HPP
#define __AST_HPP

class Node {};

class Expr {
public:
    virtual ~Expr();
};

class Type {
public:
    std::string type;
};

class FunctionParameter : Node {

};

class FunctionDecl : Node {
public:
    std::string name;

    FunctionDecl();
};

#endif // __AST_HPP