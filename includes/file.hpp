#ifndef __FILE_H
#define __FILE_H

#include <string>
#include <iostream>
#include <fstream>
#include <vector>

#include "logger.hpp"

class File;

enum TokenType {
    STRING,
    NUMBER,
    IDENTIFIER,
    OPERATOR,
    SEPARATOR,
    CHARACTER
};

static const std::string TokenTypeString[] = {
    "STRING",
    "NUMBER",
    "IDENTIFIER",
    "OPERATOR",
    "SEPARATOR",
    "CHARACTER"
};

class Token {
public:
    File *file;
    std::string content;
    TokenType type;

    Token(File *file, std::string content, TokenType type) {
        this->file = file;
        this->content = content;
        this->type = type;
    }

    std::string toString();
    std::string getTokenTypeToString();

    virtual ~Token() {}
};

class File {
public:
	/** the files location */
	std::string location;
	
	/** name of the file */
	std::string name;
	
	/** the files contents */
	std::string contents;

	/** token stream for file */
    std::vector<Token*> *tokenStream;

	/** how long the file is */
	int fileLength;

	File(std::string location);

    virtual ~File() {
        // c++ is retarded
        for (int i = 0; i < tokenStream->size(); i++) {
            delete (*tokenStream)[i];
        }
        tokenStream->clear();
    }
};

#endif // __FILE_H