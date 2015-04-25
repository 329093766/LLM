#include "parser.hpp"

bool Parser::matchToken(std::string content, TokenType type, int ahead) {
    Token *token = this->file->tokenStream->at(pos + ahead);
    if (content == "") {
        return token->type == type;
    }
    return token->type && token->content == content;
}

Node *Parser::pushNode(Node *n) {
    if (n) {
        this->file->ast->push_back(n);
        return n;
    }
    return nullptr;
}

Token *Parser::consumeToken() {
    Token *tok = this->file->tokenStream->at(pos);
    this->pos++;
    return tok;
}

Token *Parser::peek(int ahead) {
    if (pos + ahead > streamSize) {
        std::cout << peek(0)->toString() << std::endl;
        std::cerr << ahead << ", " << pos << std::endl;
        return peek(0);
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

HTML *Parser::parseHTML() {
    if (matchToken("(", SEPARATOR, 0)) {
        return parseElementDecl();
    }
    else {
        return parseElementLiteral();
    }

    return nullptr;
}

ElementLiteral *Parser::parseElementLiteral() {
    Token *tok = consumeToken();
    
    ElementLiteralType type = LIT_UNKNOWN;
    switch (tok->type) {
        case STRING: type = LIT_STRING; break;
        case CHARACTER: type = LIT_CHAR; break;
        case NUMBER: type = LIT_NUMBER; break;
        default: std::cout << "shit" << std::endl; return nullptr;
    }

    return new ElementLiteral(type, tok->content);
}

ElementDecl *Parser::parseElementDecl() {
    if (matchToken("(", SEPARATOR, 0)) {
        consumeToken();

        if (matchToken("", IDENTIFIER, 0)) {
            ElementDecl *decl = new ElementDecl(consumeToken()->content);

            while (true) {
                if (matchToken(")", SEPARATOR, 0)) {
                    consumeToken();
                    break;
                }

                HTML *node = parseHTML();
                if (node) {
                    std::cout << "k" << std::endl;
                    decl->children->push_back(node);
                }
            }

            return decl;
        } else {
            std::cerr << "no tag name!" << std::endl;
        }
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

    return nullptr;
}

FuncDecl *Parser::parseFuncDecl() {
    if (matchToken(FUNC_KEYWORD, IDENTIFIER, 0)) {
        consumeToken();

        if (matchToken("", IDENTIFIER, 0)) {
            std::string name = consumeToken()->content;
        }
    }

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

    return nullptr;
}

Node *Parser::parseNode() {
    Decl *decl = parseDecl();
    if (decl) {
        decl->codegen();
        return pushNode(decl);
    }

    HTML *html = parseHTML();
    if (html) {
        html->codegen();
        return pushNode(html);
    }

    return nullptr;
}

void Parser::parseFile(File file) {
    this->file = &file;
    this->pos = 0;
    this->streamSize = this->file->tokenStream->size();

    while (this->pos < streamSize) {
        parseNode();
    }

    std::cout << "Parsing complete" << std::endl;
}

void Parser::startParsingFiles(std::vector<File> *files) {
    for (auto &file : *files) {
        parseFile(file);
    }
}