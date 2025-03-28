//
// Created by xabdomo on 3/28/25.
//

#ifndef NATIVE_H
#define NATIVE_H

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
        V_Error,
        V_Ref
    };

    struct ValueObject {
        ValueType type;
        void* value;
    };

    typedef std::pair<std::string, std::vector<ValueType>> FunctionSignature;
    typedef ValueObject (*NativeFunction)( const FunctionSignature&, std::vector<ValueObject> );
    typedef void (* NativeAddFunction )( const FunctionSignature&, NativeFunction );
    typedef void (* NativeLoad ) (NativeAddFunction);

}
#endif //NATIVE_H
