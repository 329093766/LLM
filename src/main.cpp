#include <iostream>
#include <vector>

#include "errorhandler.hpp"
#include "file.hpp"
#include "fcgio.h"

bool isArgument(std::string argument) {
	return argument[0] == '-';
}

void handleArgument(std::string argument) {
	// cut the tack
	argument = argument.substr(1);
}


int main(int argc, char** argv) {
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

	std::streambuf *cin_streambuf  = std::cin.rdbuf();
    std::streambuf *cout_streambuf = std::cout.rdbuf();
    std::streambuf *cerr_streambuf = std::cerr.rdbuf();

    FCGX_Request request;

    FCGX_Init();
    FCGX_InitRequest(&request, 0, 0);

    while (FCGX_Accept_r(&request) == 0) {
        fcgi_streambuf cin_fcgi_streambuf(request.in);
        fcgi_streambuf cout_fcgi_streambuf(request.out);
        fcgi_streambuf cerr_fcgi_streambuf(request.err);

        std::cin.rdbuf(&cin_fcgi_streambuf);
        std::cout.rdbuf(&cout_fcgi_streambuf);
        std::cerr.rdbuf(&cerr_fcgi_streambuf);

        std::cout << "Content-type: text/html\r\n"
                << "\r\n"
                << "<html>\n"
                << "  <head>\n"
                << "    <title>Hello, World!</title>\n"
                << "  </head>\n"
                << "  <body>\n"
                << "    <h1>Praise the lord, it works!!</h1>\n"
                << "  </body>\n"
                << "</html>\n";
    }

    // restore stdio streambufs
    std::cin.rdbuf(cin_streambuf);
    std::cout.rdbuf(cout_streambuf);
    std::cerr.rdbuf(cerr_streambuf);

	return 0;
}