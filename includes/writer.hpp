#ifndef __WRITER_H
#define __WRITER_H

#include <vector>

#include "fcgio.h"
#include "logger.hpp"

/**
 * A single attribute, an attribute
 * has a name and a value. 
 */
class Attribute {
private:
	std::string name;
	std::string value;

public:
	Attribute(std::string name, std::string value) {
		this->name = name;
		this->value = value;
	}

	std::string emitAttribute() {
		return name + "=\"" + value + "\"";
	}
};

/**
 * This class represents a HTML element
 */
class Element {
protected:
	std::vector<Element*> elements;
	std::vector<Attribute*> attributes;

	std::string emitElements() {
		std::string result;
		for (Element *e : elements) {
			result += e->emitElement();
		}
		return result;
	}

	std::string emitAttributes() {
		std::string result = attributes.size() > 0 ? " " : "";

		int count = 0;
		for (Attribute *a : attributes) {
			result += a->emitAttribute();
			if (count > 1 && count != attributes.size() - 1) {
				result += " ";
			}
			count++;
		}
		
		return result;
	}

public:
	void addAttribute(Attribute *attribute) {
		attributes.push_back(attribute);
	}

	void setAttributes(std::vector<Attribute*> attributes) {
		this->attributes = attributes;
	}

	void addAttributes(std::vector<Attribute*> attributes) {
		this->attributes.insert(this->attributes.end(), attributes.begin(), attributes.end());
	}

	void addElement(Element *element) {
		elements.push_back(element);
	}

	void setElement(std::vector<Element*> element) {
		this->elements = elements;
	}

	void addElements(std::vector<Element*> elements) {
		this->elements.insert(this->elements.end(), elements.begin(), elements.end());
	}

	virtual std::string emitElement() {
		return "vagina";
	}
};

/**
 * For raw text used in paragraphs,
 * headings, etc.
 */
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

public:
	HeaderElement(int level, std::vector<Element*> elements) {
		this->level = level;
		this->elements = elements;
	}

	HeaderElement(int level, Text *text) {
		this->level = level;
		this->elements.push_back(text);
	}

	std::string emitElement() {
		std::string result = "<h" + std::to_string(level) + emitAttributes() + ">";
		result += emitElements();
		result += "</h" + std::to_string(level) + ">";
		return result;
	}
};

class ParagraphElement : public Element {
public:
	ParagraphElement(std::vector<Element*> elements) {
		this->elements = elements;
	}

	ParagraphElement(Text *text) {
		this->elements.push_back(text);
	}

	std::string emitElement() {
		std::string result = "<p>";
		result += emitElements();
		result += "</p>";
		return result;
	}
};

class AnchorElement : public Element {
public:
	AnchorElement(std::vector<Element*> elements) {
		this->elements = elements;
	}

	AnchorElement(Text *text) {
		this->elements.push_back(text);
	}

	std::string emitElement() {
		std::string result = "<p>";
		result += emitElements();
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

	void writeRaw(std::string str);

	void writeElement(Element *element);
	void writeDocument();
};

#endif // __WRITER_H