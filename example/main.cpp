#include <iostream>
#include <string>
#include "parser.tab.hpp"

extern int yyparse();
extern void yy_scan_string(const char* str);
extern void yylex_destroy();

int main() {
    std::string input;
    
    while (true) {
        std::cout << "Enter a mathematical expression (or 'quit' to exit): ";
        std::getline(std::cin, input);
        
        if (input == "quit") break;
        
        // Prepare input for parsing
        yy_scan_string(input.c_str());
        
        // Parse the input
        int parse_result = yyparse();
        
        // Clean up lexer
        yylex_destroy();
        
        if (parse_result != 0) {
            std::cerr << "Parsing failed." << std::endl;
        }
    }
    
    return 0;
}