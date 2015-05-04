#include "file.hpp"

File::File(std::string location) {
	this->location = location;
	
	// read the file into the contents
	std::ifstream file(location.c_str());
	if (!file) {
		Logger(LOGGER_ERROR) << "could not open file";
	}

	std::string line;
	while (std::getline(file, line)) {
		this->contents = this->contents + line + "\n";
	}
	std::cout << contents << std::endl;
}