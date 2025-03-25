#include "config.h"

namespace Namespace {
    Integer::Integer(int value) : value(value) {}

    Integer Integer::operator+(const Integer &other) const {
        return Integer(value + other.value);
    }

    Integer Integer::operator-(const Integer &other) const {
        return Integer(value - other.value);
    }

    Integer Integer::operator*(const Integer &other) const {
        return Integer(value * other.value);
    }

    Integer Integer::operator/(const Integer &other) const {
        return Integer(value / other.value);
    }

    Integer Integer::operator%(const Integer &other) const {
        return Integer(value % other.value);
    }

    Integer Integer::operator-() const {
        return Integer(-value);
    }

    Integer &Integer::operator++() {
        ++value;
        return *this;
    }

    Integer Integer::operator++(int) {
        Integer temp = *this;
        ++value;
        return temp;
    }

    Integer &Integer::operator--() {
        --value;
        return *this;
    }

    Integer Integer::operator--(int) {
        Integer temp = *this;
        --value;
        return temp;
    }

    bool Integer::operator==(const Integer &other) const {
        return value == other.value;
    }

    bool Integer::operator!=(const Integer &other) const {
        return value != other.value;
    }

    bool Integer::operator<(const Integer &other) const {
        return value < other.value;
    }

    bool Integer::operator>(const Integer &other) const {
        return value > other.value;
    }

    bool Integer::operator<=(const Integer &other) const {
        return value <= other.value;
    }

    bool Integer::operator>=(const Integer &other) const {
        return value >= other.value;
    }

    std::ostream &operator<<(std::ostream &os, const Integer &integer) {
        os << integer.value;
        return os;
    }

    std::istream &operator>>(std::istream &is, Integer &integer) {
        is >> integer.value;
        return is;
    }
}