#include <iostream>
#include <string>
#include "../config.h"
#include "../forward.h"
#include "../AST.h"
#include "../primitives.h"
#include "../MathHelper.h"
#include "../Values.h"
#include "../Expressions.h"

#include "parser.tab.hpp"

extern int yyparse();
extern void yy_scan_string(const char* str);
extern void yylex_destroy();

int main() {
    std::string input;
    std::cout << "Copyright © 2025 xAbdoMo. All rights reserved." << std::endl;
    std::cout << "Unauthorized copying, reproduction, or distribution of this software is strictly prohibited." << std::endl;

    while (true) {
        std::cout << ">>> ";
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