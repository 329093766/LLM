#ifndef __AST_HPP
#define __AST_HPP

class Node {};

enum Type {
    TYPE_INT,
    TYPE_DOUBLE,
    TYPE_STRING,
    TYPE_CHAR,
};

class Decl : Node {
private:
public:
};

class Expr {
public:
    virtual ~Expr();
};

class FunctionParameter {
    std::string name;
    Type type;
};

class FunctionDecl : Decl {
public:
    std::string name;
    std::vector<FunctionParameter> params;

    FunctionDecl(std::string name, std::vector<FunctionParameter> params) {
        this->name = name;
        this->params = params;
    }

    virtual ~FunctionDecl() {}
};

#endif // __AST_HPP