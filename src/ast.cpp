#include "ast.hpp"

/**
// output some html to CGI thing
writer.saveBuffers();

// test...
Text headerText("My first heading!");
HeaderElement header(1, &headerText);

Attribute attrib("style", "color: red");
header.addAttribute(&attrib);
writer.writeElement(&header);

Text paraText("This is a paragraph.");
ParagraphElement para(&paraText);
writer.writeElement(&para);

// write the document
writer.writeDocument();
*/

void VarDecl::codegen(Writer *writer) {

}

void FuncDecl::codegen(Writer *writer) {

}

void ElementLiteral::codegen(Writer *writer) {
    writer->writeRaw(content);
}

void ElementDecl::codegen(Writer *writer) {
    writer->writeRaw("<" + tag + ">");

    for (auto &child : *children) {
        child->codegen(writer);
    }

    writer->writeRaw("</" + tag + ">");
}
