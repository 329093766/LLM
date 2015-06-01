#ifndef __AST_HPP
#define __AST_HPP

#include <iostream>
#include <vector>

#include "writer.hpp"

class Node {
public:
    virtual void codegen(Writer *writer) = 0;    
};

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

class HTML : public Node {
public:
    HTML() {}
    virtual ~HTML() {}
    virtual void codegen(Writer *writer) = 0;    
};

enum ElementLiteralType {
    LIT_NUMBER,
    LIT_STRING,
    LIT_CHAR,
    LIT_UNKNOWN,
}; 

class ElementLiteral : public HTML {
public:
    ElementLiteralType type;
    std::string content;

    ElementLiteral(ElementLiteralType type, std::string content) {
        this->type = type;
        this->content = content;
    }

    virtual void codegen(Writer *writer);
};

class ElementAttribute {
public:
    std::string attribute;
    ElementLiteral *child;

    ElementAttribute(std::string attribute, ElementLiteral *child) {
        this->attribute = attribute;
        this->child = child;
    }

    virtual ~ElementAttribute() {
        delete child;
    }

    virtual void codegen(Writer *writer);
};

class ElementDecl : public HTML {
public:
    std::string tag;
    std::vector<HTML*> *children; 
    std::vector<ElementAttribute*> *attributes;

    ElementDecl(std::string tag) {
        this->tag = tag;
        this->children = new std::vector<HTML*>;
        this->attributes = new std::vector<ElementAttribute*>;
    }

    void appendChild(HTML *child) {
        this->children->push_back(child);
    }

    void appendAttrib(ElementAttribute *attrib) {
        this->attributes->push_back(attrib);
    }

    virtual ~ElementDecl() {
        this->children->clear();
        this->attributes->clear();
    }

    virtual void codegen(Writer *writer);    
};

class Decl : public Node {
public:
    Decl() {}
    virtual ~Decl() {}
    virtual void codegen(Writer *writer) = 0;    
};

class Expr {
public:
    Expr() {}
    virtual ~Expr();
    virtual void codegen(Writer *writer) = 0;    
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

    virtual void codegen(Writer *writer);
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
    virtual void codegen(Writer *writer);
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
    virtual void codegen(Writer *writer);
};

#endif // __AST_HPP