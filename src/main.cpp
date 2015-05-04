#include <iostream>

#include "errorhandler.hpp"

int main(int argc, char** argv) {
	if (argc <= 1) {
		Logger(LOGGER_ERROR) << "no input files";
	}

	for (int i = 0; i < argc; i++) {

	}

	return 0;
}