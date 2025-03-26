//
// Created by xabdomo on 3/25/25.
//

#ifndef VALUES_H
#define VALUES_H

#include <string>

#include "config.h"

namespace Namespace {
    enum ValueType {
        V_Integer,
        V_Real,
        V_String,
        V_Complex,
        V_Bool,
        V_Void,
        V_Error,
        V_Ref
    };


    struct ValueObject {
        ValueType type;
        void* value;
    };


    namespace ValuesHelper {
        class ConversionError: public std::exception {
        private:
            ValueType from;
            ValueType to;
        public:
            ConversionError(ValueType, ValueType);
            [[nodiscard]] const char *what() const noexcept override;
        };

        ValueObject castTo(ValueObject val, ValueType newType);
        ValueObject clone(ValueObject val);
        void Delete(ValueObject&);
        std::string ValueTypeAsString(ValueType);
        ValueType StringToValueType(const std::string&);
        std::string toString(ValueObject);
    }

    namespace OperationHelper {
        template<class T>
        ValueObject add(T& left, T& right) {
            return left + right;
        }
    }
};



#endif //VALUES_H
