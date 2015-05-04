#ifndef __FILE_H
#define __FILE_H

#include <string>

class File {
private:
	std::string name;
	std::string contents;
	int fileLength;

public:
	File();

	int getFileLength() {
		return this->fileLength;
	}

};

#endif // __FILE_H