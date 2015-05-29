#include "file.hpp"

std::string Token::toString() {
	return "[" + getTokenTypeToString() + "], [" + this->content + "]";
}

std::string Token::getTokenTypeToString() {
	return TokenTypeString[this->type];
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
