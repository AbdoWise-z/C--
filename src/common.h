
#ifndef COMMON_H
#define COMMON_H

#include <vector>
#include <string>

namespace Cmm {
    enum ValueType {
        V_Integer,
        V_Real,
        V_String,
        V_Complex,
        V_Bool,
        V_Void,
        V_Any
    };

    struct ValueObject {
        ValueType type;
        void* value;

        static ValueObject Void();
    };

    typedef std::pair<std::vector<ValueType>, std::vector<bool>>  FunctionDefinitionSignature;
    typedef std::pair<std::string, std::vector<ValueType>> FunctionSignature;

    typedef ValueObject (*NativeFunction)( const FunctionSignature&, std::vector<ValueObject> );
    typedef void (* NativeAddFunction )( const std::string&, const FunctionDefinitionSignature&, NativeFunction );
    typedef void (* NativeInitFunction ) (NativeAddFunction);

}
#endif //COMMON_H
