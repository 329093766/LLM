#include "lexer.hpp"

Lexer::Lexer() {

}

char Lexer::consumeCharacter() {
    if (this->pos > this->inputLength) {
        this->running = false;
        std::cerr << "reached end of input (" << this->currentChar << ")(" << this->pos << ", " << this->inputLength << ")" << std::endl;
        return '\0';
    }

    char result = this->currentChar;
    buffer += result;

    if (this->currentChar == '\n') {
        this->lineNumber++;
        this->charNumber = 0;
    }

    this->currentChar = this->file->getContent()[++this->pos];
    this->charNumber++;

    return result;
}

std::string Lexer::flushBuffer() {
    std::string result = buffer;
    buffer = "";
    return result;
}

void Lexer::recognizeOperator() {
    consumeCharacter();
    file->getTokenStream()->push_back(new Token(this->file, flushBuffer(), TokenType::OPERATOR));
}

void Lexer::recognizeSeparator() {
    consumeCharacter();
    file->getTokenStream()->push_back(new Token(this->file, flushBuffer(), TokenType::SEPARATOR));
}

void Lexer::recognizeNumber() {
    consumeCharacter();
    file->getTokenStream()->push_back(new Token(this->file, flushBuffer(), TokenType::NUMBER));
}

void Lexer::recognizeIdentifier() {
    consumeCharacter();

    while (this->currentChar == '_' || 
          (this->currentChar >= 'a' && this->currentChar <= 'z') ||
          (this->currentChar >= 'A' && this->currentChar <= 'Z')) {
        consumeCharacter();
    }

    file->getTokenStream()->push_back(new Token(this->file, flushBuffer(), TokenType::IDENTIFIER));
}

void Lexer::getNextToken() {
    switch (this->currentChar) {
        case '0' ... '9':
            recognizeNumber();
            break;
        case 'a' ... 'z':
        case 'A' ... 'Z':
            recognizeIdentifier();
            break;
        case '<': case '>':
        case '/': case '*':
        case '+': case '-':
        case '%': case '^':
        case '$': case '!':
        case '=': case '|':
        case '?': case '~':
        case '#': case ':':
        case ';': case '\\':
        case '.': case '&':
            recognizeOperator();
            break;
        case '[': case ']':
        case '(': case ')':
        case '{': case '}':
        case ',':
            recognizeSeparator();
            break;
        case '\0':
            // eof
            this->running = false;
            break;
        case ' ': case '\t': case '\n': case '\r':
            this->pos++;
            this->currentChar = this->file->getContent()[this->pos];
            break;
        default:
            std::cout << "WHAT YEAR IS IT (" << this->currentChar << ")" << std::endl;
            break;
    }
}

void Lexer::lexFile(File *file) {
    this->pos = 0;
    this->lineNumber = 1;
    this->charNumber = 1;
    this->currentChar = this->file->getContent()[this->pos];
    this->running = true;
    this->inputLength = this->file->getFileLength();

    while (this->running) {
        getNextToken();
    }
}

void Lexer::startLexingFiles(std::vector<File> files) {
    for (auto &file: files) {
        this->file = &file;
        lexFile(this->file);

        for (auto &tokens: *this->file->getTokenStream()) {
            std::cout << tokens->toString() << std::endl;
        }
    }
}