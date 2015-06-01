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
        case STRING: {
            type = LIT_STRING; 
            // remove quotes
            tok->content = tok->content.substr(1, tok->content.size() - 2);
            break;
        }
        case CHARACTER: type = LIT_CHAR; break;
        case NUMBER: type = LIT_NUMBER; break;
        default: std::cout << "shit" << std::endl; return nullptr;
    }

    return new ElementLiteral(type, tok->content);
}

ElementAttribute *Parser::parseElementAttribute() {
    if (matchToken("[", SEPARATOR, 0)) {
        consumeToken();

        if (matchToken("", IDENTIFIER, 0)) {
            ElementAttribute *attrib = new ElementAttribute(consumeToken()->content, parseElementLiteral());

            if (matchToken("]", SEPARATOR, 0)) {
                consumeToken();
                return attrib;
            } else {
                std::cerr << "no closing attribute tag thing" << std::endl;
            }
        } else {
            std::cerr << "no attribute name!" << std::endl;
        }
    }

    return nullptr;
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

                if (matchToken("[", SEPARATOR, 0)) {
                    decl->appendAttrib(parseElementAttribute());
                } else {
                    HTML *node = parseHTML();
                    if (node) {
                        decl->appendChild(node);
                    }
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

Node *Parser::parseNode(Writer *writer) {
    Decl *decl = parseDecl();
    if (decl) {
        decl->codegen(writer);
        return pushNode(decl);
    }

    HTML *html = parseHTML();
    if (html) {
        html->codegen(writer);
        return pushNode(html);
    }

    return nullptr;
}

void Parser::parseFile(File file) {
    this->file = &file;
    this->pos = 0;
    this->streamSize = this->file->tokenStream->size();

    Writer writer;

    writer.saveBuffers();

    while (this->pos < streamSize) {
        parseNode(&writer);
    }

    writer.writeDocument();

    std::cout << "Complete" << std::endl;
}

void Parser::startParsingFiles(std::vector<File> *files) {
    for (auto &file : *files) {
        parseFile(file);
    }
}