#include "parser.hpp"

bool Parser::matchToken(std::string content, TokenType type, int ahead) {
    Token *token = this->file->tokenStream->at(pos + ahead);
    if (content == "") {
        return token->type == type;
    }
    return token->type && token->content == content;
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

void Parser::parseFuncDecl() {

}

void Parser::parseDecl() {

}

void Parser::parseNode() {
    Token *currentToken = peek();

    switch (currentToken->content) {
        case FUNC_KEYWORD:
            std::cout << "it's a function!" << std::endl;
            break;
    }
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