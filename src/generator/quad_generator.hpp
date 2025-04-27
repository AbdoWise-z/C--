//
// Created by xabdomo on 4/23/25.
//

#ifndef QUAD_GENERATOR_HPP
#define QUAD_GENERATOR_HPP

#include <optional>

#include "config.h"
#include "nodes/AST.h"
#include <unordered_map>

#define QUAD_SIZE      30
#define MAX_LABEL_SIZE 0

#define OP_ASSIGN     "Assign"
#define OP_PLUS       "+"
#define OP_MINUS      "-"
#define OP_MULTIPLY   "*"
#define OP_DIVIDE     "/"
#define OP_NOT        "not"
#define OP_CAST       "cast"

#define OP_PARAM      "param"
#define OP_CALL       "call"

namespace Namespace::QuadGenerator {
    struct CodeGenScope {
        std::unordered_map<std::string, std::pair<Cmm::ValueType, bool>>                 variables;
        std::unordered_map<std::string, std::map<FunctionDefinitionSignature, Cmm::ValueType>> functions;

        bool deadCode = false;
    };

    struct ErrorBlock {
        std::string exception;
        size_t line;
    };

    typedef ErrorBlock CodeGenError;
    typedef ErrorBlock CodeGenWarn;

    struct Symbol;

    struct CodeGenContext {
        std::vector<CodeGenScope> stack;
        std::vector<CodeGenError> errors;
        std::vector<CodeGenWarn> warnings;

        std::vector<Symbol> symbolTable;

        size_t currentLine;

        size_t tempVarCount;

        size_t ifLabelCount;

        size_t forEnterLabelCount;
        size_t forExitLabelCount;
        size_t forConditionLabelCount;
        size_t forIncLabelCount;

        size_t switchCaseLabelCount;
        size_t switchCaseCondLabelCount;
        size_t switchExitLabelCount;

        std::vector<std::string> breakLabels;
        std::vector<std::string> continueLabels;
        std::vector<std::vector<ValueType>> returnLabels;

        CodeGenContext():
            stack({}),
            errors({}),
            warnings({}),
            currentLine(0),
            tempVarCount(0),
            ifLabelCount(0),
            forEnterLabelCount(0),
            forExitLabelCount(0),
            forConditionLabelCount(0),
            forIncLabelCount(0),
            switchCaseLabelCount(0),
            switchCaseCondLabelCount(0),
            switchExitLabelCount(0) {
        }
    };

    enum SymbolType {
        Variable,
        Function,
        NativeFunction,
    };

    struct Symbol {
        size_t codeLine;
        size_t quadLine; // for code generation
        size_t scope;
        std::vector<ValueType> type;
        std::vector<ValueType> accept_type;
        SymbolType objectType;

        std::string name;
        std::string value;

        // some analytics
        size_t useCount;
    };



    CodeGenContext* generate(ASTNode* root, const std::string& outputPath);
    CodeGenContext* generate(ASTNode* root, std::ostream& output);
}



#endif //QUAD_GENERATOR_HPP
