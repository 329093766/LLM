#ifndef __WRITER_H
#define __WRITER_H

#include "fcgio.h"
#include "logger.hpp"

class Element {
public:
	virtual std::string emitElement() {
		return "";
	}
};

class HeaderElement : public Element {
private:
	int level;

public:
	HeaderElement(int level) {
		this->level = level;
	}

	std::string emitElement() {
		return "<h1>test</h1>";
	}
};

class Writer {
private:
	std::streambuf *cin_streambuf;
    std::streambuf *cout_streambuf;
    std::streambuf *cerr_streambuf;
    std::string document;

    FCGX_Request request;
public:
	Writer();
	~Writer();

	void saveBuffers();
	void restoreBuffers();

	void writeElement(Element &element);
	void writeDocument();
};

#endif // __WRITER_H