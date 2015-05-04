#ifndef __FILE_H
#define __FILE_H

#include <string>
#include <iostream>
#include <fstream>

#include "errorhandler.hpp"

class File {
private:
	/** the files location */
	std::string location;
	
	/** name of the file */
	std::string name;
	
	/** the files contents */
	std::string contents;
	
	/** how long the file is */
	int fileLength;

public:
	File(std::string location);

	int getFileLength() {
		return this->fileLength;
	}

};

#endif // __FILE_H