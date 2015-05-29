#ifndef __LEXER_H
#define __LEXER_H

#include <iostream>
#include <vector>

#include "file.hpp"

class Lexer {
private:
    File *file;
    std::string buffer;

    int pos;
    int inputLength;
    int lineNumber;
    int charNumber;
    char currentChar;
    bool running;

public:
	Lexer() {

    }

    std::string flushBuffer();
    char consumeCharacter();
    void recognizeNumber();
    void recognizeOperator();
    void recognizeSeparator();
    void recognizeIdentifier();
    void getNextToken();
    void skipCharacter();
    void recognizeCharacter();
    void recognizeString();
    void lexFile(File *file);
    void startLexingFiles(std::vector<File> files);
    void pushToken(TokenType type);

    virtual ~Lexer() {

    }
};

#endif // __LEXER_H