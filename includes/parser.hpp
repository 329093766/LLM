#ifndef __PARSER_HPP
#define __PARSER_HPP

#include <vector>
#include <map>

#include "file.hpp"
#include "ast.hpp"

class Parser {
private:
    const std::string FUNC_KEYWORD = "func";
    std::map<std::string, PrimitiveType> types;

public:
    int pos;
    int streamSize;
    File *file;

    Parser() {
        types["int"] = TYPE_INT;
        types["double"] = TYPE_DOUBLE;
        types["string"] = TYPE_STRING;
        types["rune"] = TYPE_CHAR;
    }

    bool matchToken(std::string content, TokenType type, int ahead);

    Node *pushNode(Node *n);

    Type *parseType();
    VarDecl *parseVarDecl();
    FuncDecl *parseFuncDecl();
    Decl *parseDecl();
    Node *parseNode(Writer *writer);
    ElementLiteral *parseElementLiteral();
    ElementDecl *parseElementDecl();
    HTML *parseHTML();

    Token *consumeToken();
    Token *peek(int ahead = 0);

    void parseFile(File file);
    void startParsingFiles(std::vector<File> *files);

    virtual ~Parser() {}
};

#endif // __PARSER_HPP