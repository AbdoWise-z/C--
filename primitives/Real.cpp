//
// Created by xabdomo on 3/24/25.
//

#include "Real.h"

#include "Complex.h"
#include "Integer.h"

using namespace Namespace;


using namespace Namespace;

Real::Real() {
    mpf_init(mValue);
    mpf_set_d(mValue, 0.0);
}

Real::Real(const double i) {
    mpf_init(mValue);
    mpf_set_d(mValue, i);
}

Real::Real(const char* str) {
    mpf_init(mValue);
    mpf_set_str(mValue, str, 10);
}

Real::Real(const char* str, int base) {
    mpf_init(mValue);
    mpf_set_str(mValue, str, base);
}

Real::Real(const Integer &other) {
    mpf_init(mValue);
    mpf_set_z(mValue, other.mValue);
}

Real::Real(const Complex &other) {
    Real temp(0.0);
    mpf_init(mValue);
    mpf_set_d(mValue, 0.0);

    mpf_pow_ui(temp.mValue, other.real.mValue, 2);
    mpf_add(mValue, mValue, temp.mValue);
    mpf_pow_ui(temp.mValue, other.imag.mValue, 2);
    mpf_add(mValue, mValue, temp.mValue);

    mpf_sqrt(mValue, mValue);
}

Real::Real(const Real& other) {
    mpf_init(mValue);
    mpf_set(mValue, other.mValue);
}

Real &Real::operator+=(const Real &other) {
    mpf_add(mValue, mValue, other.mValue);
    return *this;
}

Real &Real::operator-=(const Real &other) {
    mpf_sub(mValue, mValue, other.mValue);
    return *this;
}

Real &Real::operator*=(const Real &other) {
    mpf_mul(mValue, mValue, other.mValue);
    return *this;
}

Real &Real::operator/=(const Real &other) {
    mpf_div(mValue, mValue, other.mValue);
    return *this;
}

Real Real::operator+(const Real &other) const {
    Real temp;
    mpf_add(temp.mValue, mValue, other.mValue);
    return temp;
}

Real Real::operator-(const Real &other) const {
    Real temp;
    mpf_sub(temp.mValue, mValue, other.mValue);
    return temp;
}

Real Real::operator*(const Real &other) const {
    Real temp;
    mpf_mul(temp.mValue, mValue, other.mValue);
    return temp;
}

Real Real::operator/(const Real &other) const {
    Real temp;
    mpf_div(temp.mValue, mValue, other.mValue);
    return temp;
}

Real::~Real() {
    if (del) {
        mpf_clear(mValue);
    }
}

bool Real::operator>(const Real &b) const {
    return mpf_cmp(mValue, b.mValue) > 0;
}

bool Real::operator<(const Real &b) const {
    return mpf_cmp(mValue, b.mValue) < 0;
}

bool Real::operator==(const Real &b) const {
    return mpf_cmp(mValue, b.mValue) == 0;
}

bool Real::operator!=(const Real &b) const {
    return mpf_cmp(mValue, b.mValue) != 0;
}

bool Real::operator>=(const Real &b) const {
    return mpf_cmp(mValue, b.mValue) >= 0;
}

bool Real::operator<=(const Real &b) const {
    return mpf_cmp(mValue, b.mValue) <= 0;
}

Real Real::operator-() const {
    Real temp;
    mpf_neg(temp.mValue, mValue);
    return temp;
}


static std::string mpfToString(const mpf_t num, int base = 10, size_t digits = 0) {
    if (digits == 0) {
        digits = mpf_get_prec(num) / 3.32;
    }

    char *str = (char *)malloc(digits + 10);
    mp_exp_t exponent;

    mpf_get_str(str, &exponent, base, digits, num);

    std::string result = str;
    free(str);

    if (exponent > 0) {
        if (exponent < result.size()) {
            result.insert(exponent, ".");
        } else {
            result.append(exponent - result.size(), '0');  // Append zeros if needed
        }
    } else {
        result = "0." + std::string(-exponent, '0') + result;  // Add leading zeros for small numbers
    }

    if (result.ends_with(".")) result.append("0");
    return result;
}


std::string Real::toString(int base) const {
    return mpfToString(mValue, base);
}

Real::Real(Real &&other) noexcept {
    memcpy(&mValue, &other.mValue, sizeof(mValue));
    other.del = false;
}

Real &Real::operator=(Real &&other) noexcept {
    memcpy(&mValue, &other.mValue, sizeof(mValue));
    other.del = false;
    return *this;
}

Real &Real::operator=(const Real &other) noexcept {
    mpf_set(mValue, other.mValue);
    return *this;
}


std::istream &Cmm::operator>>(std::istream &stream, Real &n) {
    std::string str;
    stream >> str;
    n = str.c_str();
    return stream;
}

std::ostream &Cmm::operator<<(std::ostream &stream, const Real &n) {
    stream << n.toString(10);
    return stream;
}


