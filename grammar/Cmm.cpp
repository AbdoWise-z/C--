#include <iostream>
#include <string>

// ========== must have these includes before including parser.tab ==========
#include "../config.h"
#include "../forward.h"
#include "../AST.h"
#include "../primitives.h"
#include "../MathHelper.h"
#include "../Values.h"
#include "../Expressions.h"
#include "../Program.h"

#include "parser.tab.hpp"

extern int yyparse();
extern void yy_scan_string(const char* str);
extern void yylex_destroy();

Cmm::Program::ProgramNode* root;

int main() {
    std::string input;
    std::cout << "Copyright © 2025 xAbdoMo. All rights reserved." << std::endl;
    std::cout << "Unauthorized copying, reproduction, or distribution of this software is strictly prohibited." << std::endl;

    Cmm::Program::beginScope();
    while (true) {

        std::cout << ">>> ";
        std::getline(std::cin, input);
        
        if (input == "quit") break;
        
        // Prepare input for parsing
        yy_scan_string(input.c_str());
        
        // Parse the input
        int parse_result = yyparse();
        

        if (parse_result != 0) {
            std::cerr << "Parsing failed." << std::endl;
        } else {
            // parsing is fine .. the result should in root node
            root->source->exec();
        }

        // Clean up lexer
        yylex_destroy();

    }

    Cmm::Program::endScope();
    
    return 0;
}