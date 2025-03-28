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
    // printf("Negation Operator: %s -> %s\n", this->toString(10).c_str(), temp.toString(10).c_str());
    return temp;
}

Integer Integer::operator^(const Integer &b) const {
    Integer temp;
    mpz_xor(temp.mValue , mValue , b.mValue);
    return temp;
}

static void mpz_pow(mpz_t result, const mpz_t base, const mpz_t exp) {
    if (mpz_sgn(exp) < 0) {
        mpz_set_ui(result, 0);  // Default behavior (or throw an error)
        return;
    }

    if (mpz_fits_ulong_p(exp)) {
        // If exponent is small enough, use mpz_pow_ui
        unsigned long int exp_ui = mpz_get_ui(exp);
        mpz_pow_ui(result, base, exp_ui);
    } else {
        // If exponent is too large, iterative approach
        mpz_t temp_base, temp_exp;
        mpz_init_set(temp_base, base);
        mpz_init_set(temp_exp, exp);
        mpz_set_ui(result, 1);  // result = 1

        while (mpz_sgn(temp_exp) > 0) {
            if (mpz_odd_p(temp_exp)) {
                mpz_mul(result, result, temp_base);
            }
            mpz_mul(temp_base, temp_base, temp_base);
            mpz_fdiv_q_2exp(temp_exp, temp_exp, 1);
        }

        mpz_clear(temp_base);
        mpz_clear(temp_exp);
    }
}
Integer Integer::pow(const Integer &b) const {
    Integer temp;
    mpz_pow(temp.mValue , mValue, b.mValue);
    return temp;
}

Integer Integer::operator!() const {
    return *this == 0;
}

Integer Integer::operator~() const {
    Integer temp;
    mpz_invert(temp.mValue , mValue , temp.mValue);
    return temp;
}

Integer Integer::operator>>(const Integer &b) const {
    static Integer two(2);
    Integer temp(0);
    mpz_pow_ui(temp.mValue , two.mValue , mpz_get_ui(b.mValue));
    mpz_div(temp.mValue , mValue , temp.mValue);
    return temp;
}

Integer Integer::operator<<(const Integer &b) const {
    static Integer two(2);
    Integer temp(0);
    mpz_pow_ui(temp.mValue , two.mValue , mpz_get_ui(b.mValue));
    mpz_mul(temp.mValue , mValue , temp.mValue);
    return temp;
}

Integer Integer::operator|(const Integer &b) const {
    Integer t1;
    Integer t2;

    mpz_xor(t1.mValue , b.mValue , mValue );   // this library doesn't have or, so this a little hack to do it :)
    mpz_and(t2.mValue , mValue , b.mValue);
    mpz_add(t1.mValue , t1.mValue , t2.mValue);

    return t1;
}

Integer Integer::operator&(const Integer &b) const {
    Integer t1;
    mpz_and(t1.mValue , mValue , b.mValue);
    return t1;
}

Integer Integer::sqrt() const {
    Integer t1;
    mpz_sqrt(t1.mValue , mValue );
    return t1;
}

std::string Integer::toString(int base) const {
    size_t num_bits = mpz_sizeinbase(mValue, base);  // Get required string size (including null terminator)
    char *str = (char *)malloc(num_bits + 2);  // Allocate memory for the string
    memset(str, 0, num_bits + 2);
    char* err = mpz_get_str(str, base, mValue);
    if (err == nullptr) {
        throw std::runtime_error("Failed to convert integer to string");
    }
    str[num_bits + 1] = '\0';
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