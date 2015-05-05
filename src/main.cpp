#include <iostream>
#include <vector>

#include "logger.hpp"
#include "file.hpp"
#include "writer.hpp"

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

	std::vector<File> files;

	// loop through all arguments except
	// for the executable
	for (int i = 1; i < argc; i++) {
		if (isArgument(argv[i])) {
			handleArgument(argv[i]);
		}
		else {
			// it's a file?
			File file(argv[i]);
			files.push_back(file);
		}
	}

	writer.saveBuffers();

	Text headerText("My first heading!");
	HeaderElement header(1, &headerText);

	Attribute attrib("style", "color: red");
	header.addAttribute(&attrib);
	writer.writeElement(&header);

	Text paraText("This is a paragraph.");
	ParagraphElement para(&paraText);
	writer.writeElement(&para);

	writer.writeDocument();

	return 0;
}