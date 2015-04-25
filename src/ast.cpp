#include "ast.hpp"

void VarDecl::codegen() {
    std::cout << "VarDecl!" << std::endl;
}

void FuncDecl::codegen() {
    std::cout << "FuncDecl!" << std::endl;
}

void ElementLiteral::codegen() {
    std::cout << "ElementLiteral!" << std::endl;
}

void ElementDecl::codegen() {
    std::cout << "ElementDecl!" << std::endl;
}
