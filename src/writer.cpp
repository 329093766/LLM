#include "writer.hpp"

Writer::Writer() {
	document = "Content-type: text/html\r\n\r\n<html><body>";
}

void Writer::writeDocument() {
    FCGX_Init();
    FCGX_InitRequest(&request, 0, 0);

    // close dat html tag bby
    document += "</body></html>";

    while (FCGX_Accept_r(&request) == 0) {
        fcgi_streambuf cin_fcgi_streambuf(request.in);
        fcgi_streambuf cout_fcgi_streambuf(request.out);
        fcgi_streambuf cerr_fcgi_streambuf(request.err);

        std::cin.rdbuf(&cin_fcgi_streambuf);
        std::cout.rdbuf(&cout_fcgi_streambuf);
        std::cerr.rdbuf(&cerr_fcgi_streambuf);

        std::cout << document;
    }

    std::cout << document << std::endl;
}

void Writer::writeElement(Element *element) {
	document += element->emitElement();
}

void Writer::saveBuffers() {
	this->cin_streambuf  = std::cin.rdbuf();
    this->cout_streambuf = std::cout.rdbuf();
    this->cerr_streambuf = std::cerr.rdbuf();
}

void Writer::restoreBuffers() {
    std::cin.rdbuf(this->cin_streambuf);
    std::cout.rdbuf(this->cout_streambuf);
    std::cerr.rdbuf(this->cerr_streambuf);
}

Writer::~Writer() {
	restoreBuffers();
}