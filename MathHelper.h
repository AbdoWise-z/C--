//
// Created by xabdomo on 3/25/25.
//

#ifndef MATHHELPER_H
#define MATHHELPER_H

#include <stdexcept>

#include "config.h"
#include "Values.h"

namespace Namespace {

    namespace MathHelper {

        class OperationError: public std::exception {
        private:
            ValueType from;
            ValueType to;
            std::string op;
        public:
            OperationError(ValueType, ValueType, const std::string&);
            const char *what() const noexcept override;
        };

        ValueObject add(ValueObject& left, ValueObject& right);
        ValueObject sub(ValueObject& left, ValueObject& right);
        ValueObject mul(ValueObject& left, ValueObject& right);
        ValueObject div(ValueObject& left, ValueObject& right);

        // ValueObject lshift(ValueObject& left, ValueObject& right);
        // ValueObject rshift(ValueObject& left, ValueObject& right);
        // ValueObject bitwise_or(ValueObject& left, ValueObject& right);
        // ValueObject bitwise_and(ValueObject& left, ValueObject& right);
        // ValueObject bitwise_xor(ValueObject& left, ValueObject& right);
        //
        // ValueObject logical_or(ValueObject& left, ValueObject& right);
        // ValueObject logical_and(ValueObject& left, ValueObject& right);
        // ValueObject bitwise_not(ValueObject& left);
        //
        // ValueObject invert(ValueObject& left);
    }

}


#endif //MATHHELPER_H
