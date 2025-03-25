//
// Created by xabdomo on 3/24/25.
//

#include "Integer.h"

#include "Complex.h"
#include "Real.h"

using namespace Namespace;

Integer::Integer() {
    mpz_init(mValue);
    mpz_set_si(mValue , 0);
}

Integer::Integer(int i) {
    mpz_init(mValue);
    mpz_set_si(mValue , i);
}

Integer::Integer(long i) {
    mpz_init(mValue);
    mpz_set_si(mValue , i);
}

Integer::Integer(const char* str) {
    mpz_init(mValue);
    mpz_set_str(mValue , str , 10);
}

Integer::Integer(const char *str, int base) {
    mpz_init(mValue);
    mpz_set_str(mValue , str , base);
}


Integer::Integer(const Integer& other) {
    mpz_init(mValue);
    mpz_set(mValue , other.mValue);
}

Integer::Integer(const Complex &other) {
    mpz_init(mValue);
    mpz_set_f(mValue , other.real.mValue);
}

Integer::Integer(const Real &other) {
    mpz_init(mValue);
    mpz_set_f(mValue , other.mValue);
}

Integer &Integer::operator+=(const Integer &other) {
    mpz_add(mValue, mValue, other.mValue);
    return *this;
}

Integer &Integer::operator-=(const Integer &other) {
    mpz_sub(mValue, mValue, other.mValue);
    return *this;
}

Integer &Integer::operator*=(const Integer &other) {
    mpz_mul(mValue, mValue, other.mValue);
    return *this;
}

Integer &Integer::operator/=(const Integer &other) {
    mpz_div(mValue, mValue, other.mValue);
    return *this;
}

Integer &Integer::operator%=(const Integer &other) {
    mpz_mod(mValue, mValue, other.mValue);
    return *this;
}

Integer Integer::operator+(const Integer &other) const {
    Integer temp;
    mpz_add(temp.mValue , mValue , other.mValue);
    return temp;
}

Integer Integer::operator-(const Integer &other) const {
    Integer temp;
    mpz_sub(temp.mValue , mValue , other.mValue);
    return temp;
}


Integer Integer::operator*(const Integer &other) const {
    Integer temp;
    mpz_mul(temp.mValue , mValue , other.mValue);
    return temp;
}

Integer Integer::operator/(const Integer &other) const {
    Integer temp;
    mpz_div(temp.mValue , mValue , other.mValue);
    return temp;
}

Integer Integer::operator%(const Integer &other) const {
    Integer temp;
    mpz_mod(temp.mValue , mValue , other.mValue);
    return temp;
}

Integer::~Integer() {
    if (del) {
        mpz_clear(mValue);
    }
}

bool Integer::operator>(const Integer &b) const {
    return mpz_cmp(mValue , b.mValue) == 1;
}

bool Integer::operator<(const Integer &b) const {
    return mpz_cmp(mValue , b.mValue) == -1;
}

bool Integer::operator==(const Integer &b) const {
    return mpz_cmp(mValue , b.mValue) == 0;
}

bool Integer::operator!=(const Integer &b) const {
    return mpz_cmp(mValue , b.mValue) != 0;
}

bool Integer::operator>=(const Integer &b) const {
    return mpz_cmp(mValue , b.mValue) >= 0;
}

bool Integer::operator<=(const Integer &b) const {
    return mpz_cmp(mValue , b.mValue) <= 0;
}


Integer Integer::operator-() const {
    Integer temp;
    mpz_neg(temp.mValue , mValue);
    return temp;
}

Integer Integer::operator^(const Integer &b) const {
    Integer temp;
    mpz_xor(temp.mValue , mValue , b.mValue);
    return temp;
}

Integer Integer::operator!() const {
    Integer temp;
    mpz_invert(temp.mValue , mValue , temp.mValue);
    return temp;
}

std::string Integer::toString(int base) const {
    size_t num_bits = mpz_sizeinbase(mValue, base);  // Get required string size (including null terminator)
    char *str = (char *)malloc(num_bits + 1);  // Allocate memory for the string
    // Convert var to a string in base 10
    char* err = mpz_get_str(str, base, mValue);  // 10 for base 10 conversion
    if (err == nullptr) {
        throw "Failed to convert to string";
    }
    str[num_bits] = '\0';
    std::string out = str;
    free (str);
    return out;
}

std::istream &Cmm::operator>>(std::istream &stream, Integer &n) {
    std::string str;
    stream >> str;
    n = str.c_str();
    return stream;
}

std::ostream &Cmm::operator<<(std::ostream &stream, const Integer &n) {
    stream << n.toString(10);
    return stream;
}

Integer::Integer(Integer &&other)  noexcept {
    memcpy(&mValue , &other.mValue , sizeof(mValue));
    other.del = false;
}

Integer &Integer::operator=(Integer &&other)  noexcept {
    memcpy(&mValue , &other.mValue , sizeof(mValue));
    other.del = false;
    return *this;
}

Integer &Integer::operator=(const Integer &other) noexcept {
    mpz_set(mValue , other.mValue);
    return *this;
}