#ifndef __AST_HPP
#define __AST_HPP

class Node {};

enum PrimitiveType {
    TYPE_INT,
    TYPE_DOUBLE,
    TYPE_STRING,
    TYPE_CHAR,
};

class Type {
public:
    PrimitiveType type;

    Type(PrimitiveType type) {
        this->type = type;
    }
};

class Decl : public Node {
public:
    Decl() {}
    virtual ~Decl() {}
};

class Expr {
public:
    Expr() {}
    virtual ~Expr();
};

class VarDecl : public Decl {
public:
    std::string name;
    Type *type;
    Expr *value;

    VarDecl(std::string name, Type *type) {
        this->name = name;
        this->type = type;
    }

    virtual ~VarDecl() { }
};

class FuncParam {
public:
    std::string name;
    Type *type;

    FuncParam(std::string name, Type *type) {
        this->name = name;
        this->type = type;
    }

    virtual ~FuncParam() {}
};

class FuncDecl : public Decl {
public:
    std::string name;
    std::vector<FuncParam> params;

    FuncDecl(std::string name, std::vector<FuncParam> params) {
        this->name = name;
        this->params = params;
    }

    virtual ~FuncDecl() {}
};

#endif // __AST_HPP