#include <iostream>
#include <vector>

#include "logger.hpp"
#include "file.hpp"
#include "writer.hpp"
#include "lexer.hpp"
#include "parser.hpp"

bool isArgument(std::string argument) {
	return argument[0] == '-';
}

void handleArgument(std::string argument) {
	// cut the tack
	argument = argument.substr(1);
}

int main(int argc, char** argv) {
	Writer writer;

	// no arguments, what a noob
	if (argc <= 1) {
		Logger(LOGGER_ERROR) << "no input files";
	}

	std::vector<File> *files = new std::vector<File>;

	// loop through all arguments except
	// for the executable
	for (int i = 1; i < argc; i++) {
		if (isArgument(argv[i])) {
			handleArgument(argv[i]);
		}
		else {
			// it's a file?
			File file(argv[i]);
			files->push_back(file);
		}
	}

	Lexer lexer;
	lexer.startLexingFiles(files);

	Parser parser;
	parser.startParsingFiles(files);

	files->clear();

	return 0;
}
