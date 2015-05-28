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
};

static const std::string TokenTypeString[] = {
    "STRING",
    "NUMBER",
    "IDENTIFIER",
    "OPERATOR",
    "SEPARATOR",
};

class Token {
private:
    File *file;
    std::string content;
    TokenType type;

public:
    Token(File *file, std::string content, TokenType type) {
        this->file = file;
        this->content = content;
        this->type = type;
    }

    File *getFile();
    std::string getContent();
    std::string toString();
    std::string getTokenTypeToString();
    TokenType getType();

    virtual ~Token() {}
};

class File {
private:
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

public:
	File(std::string location);

	std::string getName();
	std::string getContent();
	std::vector<Token*> *getTokenStream();
	int getFileLength();

    virtual ~File() {
        // c++ is retarded
        for (int i = 0; i < tokenStream->size(); i++) {
            delete (*tokenStream)[i];
        }
        tokenStream->clear();
    }
};

#endif // __FILE_H