#include <iostream>
#include <gmp.h>

#include "AST.h"
#include "Expressions.h"


int main() {
    Cmm::EvaluableNode* ptr = new Cmm::Expressions::NegatedNode(new Cmm::Expressions::ConstantValueNode(Cmm::Real(1.0)));

    try {
        auto result = ptr->eval();
        auto asStr = Cmm::ValuesHelper::castTo(result, Cmm::V_String);
        auto str_ptr = static_cast<Cmm::String*>(asStr.value);
        std::cout << *str_ptr << std::endl;
    } catch (std::exception e) {
        std::cerr << e.what() << std::endl;
    }
}
