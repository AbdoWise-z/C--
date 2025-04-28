
#ifndef MATHHELPER_H
#define MATHHELPER_H

#include <stdexcept>

#include "config.h"
#include "Values.h"
#include "primitives/Real.h"

namespace Namespace {

    namespace MathHelper {

        class OperationError: public std::exception {
        private:
            ValueType from;
            ValueType to;
            std::string op;
        public:
            OperationError(ValueType, ValueType, const std::string&);
            [[nodiscard]] const char *what() const noexcept override;
        };

        // normal stuff
        ValueObject add(ValueObject& left, ValueObject& right);
        ValueObject sub(ValueObject& left, ValueObject& right);
        ValueObject mul(ValueObject& left, ValueObject& right);
        ValueObject div(ValueObject& left, ValueObject& right);
        ValueObject mod(ValueObject& left, ValueObject& right);

        // bits operations
        ValueObject lshift(ValueObject& left, ValueObject& right);
        ValueObject rshift(ValueObject& left, ValueObject& right);
        ValueObject bitwise_or(ValueObject& left, ValueObject& right);
        ValueObject bitwise_and(ValueObject& left, ValueObject& right);
        ValueObject bitwise_xor(ValueObject& left, ValueObject& right);
        ValueObject bitwise_not(ValueObject& left);

        // logical operations
        ValueObject logical_or(ValueObject& left, ValueObject& right);
        ValueObject logical_and(ValueObject& left, ValueObject& right);
        ValueObject logical_not(ValueObject& left);

        // comparisons
        ValueObject equal(ValueObject& left, ValueObject& right);
        ValueObject greater(ValueObject& left, ValueObject& right);
        ValueObject less(ValueObject& left, ValueObject& right);
        ValueObject greater_equal(ValueObject& left, ValueObject& right);
        ValueObject less_equal(ValueObject& left, ValueObject& right);
        ValueObject not_equal(ValueObject& left, ValueObject& right);

        class DivisionByZeroError : public std::exception {
        public:
            DivisionByZeroError();
            [[nodiscard]] const char *what() const noexcept override;
        };
    }

}


#endif //MATHHELPER_H
