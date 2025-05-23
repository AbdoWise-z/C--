
#ifndef VALUES_H
#define VALUES_H

#include <map>
#include <set>
#include <string>

#include "config.h"
#include "common.h"

namespace Namespace {

    const extern std::map<std::pair<Cmm::ValueType, Cmm::ValueType>, Cmm::ValueType> TermConversionMap;

    const extern std::map<Cmm::ValueType , std::set<Cmm::ValueType>> CastConversionMap;

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
