#ifndef __PARSER_HPP
#define __PARSER_HPP

#include <vector>

#include "file.hpp"
#include "ast.hpp"

#define FUNC_KEYWORD "func"

/**
 * shamelessy stolen from https://stackoverflow.com/questions/16388510/evaluate-a-string-with-a-switch-in-c
 */
constexpr unsigned int stringAsInt(const char* str, int h = 0) {
    return !str[h] ? 5381 : (stringAsInt(str, h+1) * 33) ^ str[h];
}

class Parser {
public:
    int pos;
    File *file;

    Parser() {}

    bool matchToken(std::string content, TokenType type, int ahead);

    void parseFuncDecl();
    void parseDecl();
    void parseNode();

    Token *consumeToken();
    Token *peek(int ahead = 0);

    void parseFile(File file);
    void startParsingFiles(std::vector<File> *files);

    virtual ~Parser() {}
};

#endif // __PARSER_HPP