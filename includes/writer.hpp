#ifndef __WRITER_H
#define __WRITER_H

#include <vector>

#include "fcgio.h"
#include "logger.hpp"

class Element {
public:
	virtual std::string emitElement() {
		return "";
	}
};

class Text : public Element {
private:
	std::string value;

public:
	Text(std::string value) {
		this->value = value;
	}

	std::string emitElement() {
		return this->value;
	}
};

class HeaderElement : public Element {
private:
	int level;
	std::vector<Element*> elements;

public:
	HeaderElement(int level, std::vector<Element*> elements) {
		this->level = level;
		this->elements = elements;
	}

	HeaderElement(int level, Text text) {
		this->level = level;
		this->elements.push_back(&text);
	}

	std::string emitElement() {
		std::string result = "<h" + std::to_string(level) + ">";
		for (Element *e : this->elements) {
			result += e->emitElement();
		}
		result += "</h" + std::to_string(level) + ">";
		return result;
	}
};

class ParagraphElement : public Element {
private:
	std::vector<Element*> elements;

public:
	ParagraphElement(std::vector<Element*> elements) {
		this->elements = elements;
	}

	ParagraphElement(Text text) {
		this->elements.push_back(&text);
	}

	std::string emitElement() {
		std::string result = "<p>";
		for (Element *e : this->elements) {
			result += e->emitElement();
		}
		result += "</p>";
		return result;
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