
#include "Values.h"
#include "primitives.h"


namespace Cmm {

    const std::map<std::pair<Cmm::ValueType, Cmm::ValueType>, Cmm::ValueType> TermConversionMap = {
        {{Cmm::V_Bool, Cmm::V_Bool}, Cmm::V_Bool},
        {{Cmm::V_Bool, Cmm::V_Integer}, Cmm::V_Integer},
        {{Cmm::V_Bool, Cmm::V_Real}, Cmm::V_Real},
        {{Cmm::V_Bool, Cmm::V_Complex}, Cmm::V_Complex},
        {{Cmm::V_Bool, Cmm::V_String}, Cmm::V_String},
        {{Cmm::V_Bool, Cmm::V_Any}, Cmm::V_Any},

        {{Cmm::V_Integer, Cmm::V_Bool}, Cmm::V_Integer},
        {{Cmm::V_Integer, Cmm::V_Integer}, Cmm::V_Integer},
        {{Cmm::V_Integer, Cmm::V_Real}, Cmm::V_Real},
        {{Cmm::V_Integer, Cmm::V_Complex}, Cmm::V_Complex},
        {{Cmm::V_Integer, Cmm::V_String}, Cmm::V_String},
        {{Cmm::V_Integer, Cmm::V_Any}, Cmm::V_Any},

        {{Cmm::V_Real, Cmm::V_Bool}, Cmm::V_Real},
        {{Cmm::V_Real, Cmm::V_Integer}, Cmm::V_Real},
        {{Cmm::V_Real, Cmm::V_Real}, Cmm::V_Real},
        {{Cmm::V_Real, Cmm::V_Complex}, Cmm::V_Complex},
        {{Cmm::V_Real, Cmm::V_String}, Cmm::V_String},
        {{Cmm::V_Real, Cmm::V_Any}, Cmm::V_Any},

        {{Cmm::V_Complex, Cmm::V_Bool}, Cmm::V_Complex},
        {{Cmm::V_Complex, Cmm::V_Integer}, Cmm::V_Complex},
        {{Cmm::V_Complex, Cmm::V_Real}, Cmm::V_Complex},
        {{Cmm::V_Complex, Cmm::V_Complex}, Cmm::V_Complex},
        {{Cmm::V_Complex, Cmm::V_String}, Cmm::V_String},
        {{Cmm::V_Complex, Cmm::V_Any}, Cmm::V_Any},

        {{Cmm::V_String, Cmm::V_Bool}, Cmm::V_String},
        {{Cmm::V_String, Cmm::V_Integer}, Cmm::V_String},
        {{Cmm::V_String, Cmm::V_Real}, Cmm::V_String},
        {{Cmm::V_String, Cmm::V_Complex}, Cmm::V_String},
        {{Cmm::V_String, Cmm::V_String}, Cmm::V_String},
        {{Cmm::V_String, Cmm::V_Any}, Cmm::V_Any},

        {{Cmm::V_Any, Cmm::V_Bool}, Cmm::V_Any},
        {{Cmm::V_Any, Cmm::V_Integer}, Cmm::V_Any},
        {{Cmm::V_Any, Cmm::V_Real}, Cmm::V_Any},
        {{Cmm::V_Any, Cmm::V_Complex}, Cmm::V_Any},
        {{Cmm::V_Any, Cmm::V_String}, Cmm::V_Any},
        {{Cmm::V_Any, Cmm::V_Any}, Cmm::V_Any},
    };

    const std::map<Cmm::ValueType , std::set<Cmm::ValueType>> CastConversionMap = {
        {V_Integer, {V_Integer, V_Real, V_Complex, V_Bool, V_String, V_Any}},
        {V_Real   , {V_Integer, V_Real, V_Complex, V_Bool, V_String, V_Any}},
        {V_Complex, {V_Integer, V_Real, V_Complex, V_Bool, V_String, V_Any}},
        {V_String , {V_Integer, V_Real,            V_Bool, V_String, V_Any}},
        {V_Bool   , {V_Integer, V_Real, V_Complex, V_Bool, V_String, V_Any}},
        {V_Any    , {V_Any}},
        {V_Void   , {}},
    };
}

std::string Cmm::ValuesHelper::ValueTypeAsString(ValueType v) {
    if (v == V_Integer) return "int";
    if (v == V_Real) return "real";
    if (v == V_String) return "str";
    if (v == V_Bool) return "bool";
    if (v == V_Complex) return "complex";
    if (v == V_Void) return "void";
    if (v == V_Any) return "any";
    // if (v == V_Error) return "error";
    // if (v == V_Ref) return "ref";

    return "wtf";
}

Cmm::ValueType Cmm::ValuesHelper::StringToValueType(const std::string& v) {
    if (v == "int") return V_Integer;
    if (v == "real") return V_Real;
    if (v == "str") return V_String;
    if (v == "bool") return V_Bool;
    if (v == "complex") return V_Complex;
    if (v == "void") return V_Void;
    if (v == "any") return V_Any;
    // if (v == "error") return V_Error;
    // if (v == "ref") return V_Ref;

    return static_cast<ValueType>(-1); // wtf xD
}

std::string Cmm::ValuesHelper::toString(ValueObject v) {
    //TODO: maybe fix this later ...
    if (v.type == V_Void) return "void";
    // if (v.type == V_Error) return "err";
    // if (v.type == V_Ref) return "ref";

    ValueObject temp = castTo(v, V_String);
    auto str = static_cast<String*>(temp.value);
    std::string result = *str;
    Delete(temp);
    return result;
}

void Cmm::ValuesHelper::Delete(ValueObject& val) {
    if (val.value == nullptr) return;

    switch (val.type) {
        case V_Real:
            delete static_cast<Real *>(val.value);
        break;
        case V_Integer:
            delete static_cast<Integer *>(val.value);
        break;
        case V_Complex:
            delete static_cast<Complex *>(val.value);
        break;
        case V_Bool:
            // delete static_cast<bool *>(obj.value);
            break;
        case V_String:
            delete static_cast<String *>(val.value);
        break;
        default:
            break;
    }
}


Cmm::ValueObject Cmm::ValuesHelper::castTo(ValueObject val, ValueType newType) {
    ValueObject newVal {
        .type = newType,
        .value = nullptr,
    };

    if (val.type == V_Integer) {
        auto integer_ptr = static_cast<Integer*>(val.value);
        if (newType == V_Integer) newVal.value = new Integer(*integer_ptr);
        else if (newType == V_Real) newVal.value = new Real(*integer_ptr);
        else if (newType == V_Complex) newVal.value = new Complex(*integer_ptr);
        else if (newType == V_Bool) newVal.value = static_cast<void*>(*integer_ptr != 0 ? reinterpret_cast<int *>(1) : static_cast<int *>(0));
        else if (newType == V_String) newVal.value = new String(integer_ptr->toString(10));
        else {
            throw ConversionError(val.type, newType);
        }

        return newVal;
    }

    if (val.type == V_Real) {
        auto ptr = static_cast<Real*>(val.value);
        if (newType == V_Integer) newVal.value = new Integer(*ptr);
        else if (newType == V_Real) newVal.value = new Real(*ptr);
        else if (newType == V_Complex) newVal.value = new Complex(*ptr);
        else if (newType == V_Bool) newVal.value = *ptr != 0.0 ? reinterpret_cast<int *>(1) : static_cast<int *>(0);
        else if (newType == V_String) newVal.value = new String(ptr->toString(10));
        else {
            throw ConversionError(val.type, newType);
        }

        return newVal;
    }

    if (val.type == V_Complex) {
        auto ptr = static_cast<Complex*>(val.value);
        if (newType == V_Integer) newVal.value = new Integer(*ptr);
        else if (newType == V_Real) newVal.value = new Real(*ptr);
        else if (newType == V_Complex) newVal.value = new Complex(*ptr);
        else if (newType == V_Bool) newVal.value = static_cast<void*>(ptr->getRealPart() != 0.0 || ptr->getImagPart() != 0.0 ? reinterpret_cast<int *>(1) : static_cast<int *>(0));
        else if (newType == V_String) newVal.value = new String(ptr->toString());
        else {
            throw ConversionError(val.type, newType);
        }

        return newVal;
    }

    if (val.type == V_String) {
        auto ptr = static_cast<String*>(val.value);
        if (newType == V_Integer) newVal.value = new Integer(ptr->c_str());
        else if (newType == V_Real) newVal.value = new Real(ptr->c_str());
        //else if (newType == V_Complex) newVal.value = new Complex(ptr->c_str()); //fixme: this should be doable, but I'm to lazy to implement it
        else if (newType == V_Bool) newVal.value = reinterpret_cast<void*>(!ptr->empty());
        else if (newType == V_String) newVal.value = new String(*ptr);
        else {
            throw ConversionError(val.type, newType);
        }

        return newVal;
    }

    if (val.type == V_Bool) {
        auto ptr = val.value;
        if (newType == V_Integer) newVal.value = new Integer(ptr != nullptr ? 1 : 0);
        else if (newType == V_Real) newVal.value = new Real(ptr != nullptr ? 1 : 0);
        else if (newType == V_Complex) newVal.value = new Complex(ptr != nullptr ? 1 : 0, 0);
        else if (newType == V_Bool) newVal.value = ptr;
        else if (newType == V_String) newVal.value = new String(ptr != nullptr ? "true" : "false");
        else {
            throw ConversionError(val.type, newType);
        }

        return newVal;
    }

    throw ConversionError(val.type, newType);
}

Cmm::ValueObject Cmm::ValuesHelper::clone(ValueObject val) {
    if (val.type == V_Void) {
        return {
            .type = val.type,
            .value = nullptr
        };
    }

    // if (val.type == V_Ref) {
    //     // a little hack
    //     val.type = V_String;
    //     auto clone = castTo(val, V_String);
    //     clone.type = V_String;
    //     return clone;
    // }

    return castTo(val, val.type);
}


Cmm::ValuesHelper::ConversionError::ConversionError(ValueType a, ValueType b): exception() {
    this->from = a;
    this->to = b;
}

const char * Cmm::ValuesHelper::ConversionError::what() const noexcept {
    static std::string str;
    str =  "Cannot convert from type ";
    str += ValueTypeAsString(from);
    str += " to ";
    str += ValueTypeAsString(to);
    str += " : Unknown conversion";

    return str.c_str();
}
