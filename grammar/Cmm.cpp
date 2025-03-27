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
#include "../editor/NanoEditor.h"

extern int yyparse();
extern void yy_scan_string(const char* str);
extern void yylex_destroy();

Cmm::Program::ProgramNode* root;


int main() {
    std::ios::sync_with_stdio(false);

    yydebug = 0;
    std::string input;
    std::cout << "Copyright © 2025 xAbdoMo. All rights reserved." << std::endl;
    std::cout << "Unauthorized copying, reproduction, or distribution of this software is strictly prohibited." << std::endl;
    std::cout << "Type 'editor' to open code editor, 'quit' to exit, or any Cmm statement to execute." << std::endl;

    Cmm::Program::beginScope();
    while (true) {

        std::cout << ">>> ";
        std::getline(std::cin, input);

        if (input == "editor") {
            input = NanoEditor::edit();
        }

        if (input == "quit") break;
        if (input.empty()) break;

        if (!input.ends_with(';')) {
            input += ";"; // even if we shouldn't it wont make a problem
        }

        yy_scan_string(input.c_str());
        
        int parse_result = yyparse();

        if (parse_result == 0) {
            root->source->exec();
        }

        // Clean up lexer
        yylex_destroy();
    }

    Cmm::Program::endScope();
    
    return 0;
}