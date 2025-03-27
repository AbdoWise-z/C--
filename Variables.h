//
// Created by xabdomo on 3/27/25.
//

#ifndef VARIABLES_H
#define VARIABLES_H

#include "config.h"
#include "Expressions.h"
#include "Program.h"

namespace Namespace::Variables {
    class VariableDeclarationNode: public ExecutableNode {
    public:
        bool isConst;
        std::string name;
        std::string type;
        EvaluableNode* value;
        VariableDeclarationNode(bool isConst, std::string name, std::string type, EvaluableNode* value);
        void exec() override;
        ~VariableDeclarationNode() override;
    };

    class VariableAssignmentNode: public ExecutableNode {
    public:
        std::string name;
        EvaluableNode* expr;
        VariableAssignmentNode(std::string name, EvaluableNode* value);
        void exec() override;
        ~VariableAssignmentNode() override;
    };

    class CompoundAssignmentNode: public ExecutableNode {
    public:
        VariableAssignmentNode* _internal;
        CompoundAssignmentNode(const std::string& name, const std::string &op, EvaluableNode* value);
        void exec() override;
        ~CompoundAssignmentNode() override;
    };

    class PreIncNode: public EvaluableNode {
    public:
        Expressions::TermNode* _internal;
        std::string name;
        PreIncNode(const std::string& name, const std::string &op);
        ValueObject eval() override;
        ~PreIncNode() override;
    };

};



#endif //VARIABLES_H
