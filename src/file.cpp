#include "file.hpp"

File *Token::getFile() {
    return this->file;
}

std::string Token::getContent() {
    return this->content;
}

std::string Token::toString() {
	return "[" + getTokenTypeToString() + "], [" + this->content + "]";
}

std::string Token::getTokenTypeToString() {
	return TokenTypeString[this->type];
}

TokenType Token::getType() {
    return this->type;
}

File::File(std::string location) {
	this->location = location;
	
	// read the file into the contents
	std::ifstream file(location.c_str());
	if (!file) {
		Logger(LOGGER_ERROR) << "could not open file";
		return;
	}

	std::string line;
	while (std::getline(file, line)) {
		this->contents = this->contents + line + "\n";
	}

	this->fileLength = this->contents.length();
	this->tokenStream = new std::vector<Token*>;
}

std::string File::getName() {
	return this->name;
}

std::string File::getContent() {
	return this->contents;
}

std::vector<Token*> *File::getTokenStream() {
	return this->tokenStream;
}

int File::getFileLength() {
	return this->fileLength;
}