#include "parser.hpp"

bool Parser::matchToken(std::string content, TokenType type, int ahead) {
    Token *token = this->file->tokenStream->at(pos + ahead);
    if (content == "") {
        return token->type == type;
    }
    return token->type && token->content == content;
}

Node *Parser::pushNode(Node *n) {
    this->file->ast->push_back(n);
    return n;
}

Token *Parser::consumeToken() {
    Token *tok = this->file->tokenStream->at(pos);
    this->pos++;
    return tok;
}

Token *Parser::peek(int ahead) {
    if (ahead > pos) {
        std::cerr << "shit" << std::endl;
        return nullptr;
    }
    return file->tokenStream->at(pos + ahead);
}

Type *Parser::parseType() {
    std::string value = consumeToken()->content;
    if (types.find(value) != types.end()) {
        return new Type(types[value]);
    }
    return nullptr;
}

// a : type = expr
VarDecl *Parser::parseVarDecl() {
    if (matchToken("", IDENTIFIER, 0)) {
        std::string name = consumeToken()->content;

        if (matchToken(":", OPERATOR, 0)) {
            consumeToken();
        }

        Type *type = parseType();
        if (!type) {
            std::cerr << "invalid type" << std::endl;
        }

        VarDecl *var = new VarDecl(name, type);
        if (matchToken("=", OPERATOR, 0)) {
            consumeToken();

            // parse expr
            // add it on the to the *var
        }

        return var;
    }

    std::cout << "shitty var decl" << std::endl;
    return nullptr;
}

FuncDecl *Parser::parseFuncDecl() {
    if (matchToken(FUNC_KEYWORD, IDENTIFIER, 0)) {
        consumeToken();

        if (matchToken("", IDENTIFIER, 0)) {
            std::string name = consumeToken()->content;
        }
    }

    std::cout << "shitty func decl" << std::endl;
    return nullptr;
}

Decl *Parser::parseDecl() {
    if (peek()->content == FUNC_KEYWORD) {
        FuncDecl *func = parseFuncDecl();
        // todo
        return func;
    }
    else if (peek(1)->type == OPERATOR && peek(1)->content == ":") {
        VarDecl *decl = parseVarDecl();
        return decl;
    }

    std::cout << "shitty decl" << std::endl;
    return nullptr;
}

Node *Parser::parseNode() {
    Decl *decl = parseDecl();
    if (decl) {
        return pushNode(decl);
    }

    std::cout << "shitty node" << std::endl;
    return nullptr;
}

void Parser::parseFile(File file) {
    this->file = &file;
    this->pos = 0;

    int tokenStreamSize = this->file->tokenStream->size();
    while (this->pos < tokenStreamSize) {
        parseNode();
    }

    std::cout << "DONE!" << std::endl;
}

void Parser::startParsingFiles(std::vector<File> *files) {
    for (auto &file : *files) {
        parseFile(file);
    }
}