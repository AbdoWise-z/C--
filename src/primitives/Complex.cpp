
#include "Complex.h"
#include <iostream>

using namespace Namespace;

Complex::Complex() : real(0.0), imag(0.0) {}

Complex::Complex(const Real &r, const Real &i) : real(r), imag(i) {}

Complex::Complex(double r, double i) : real(r), imag(i) {}

Complex::Complex(const Complex &other) : real(other.real), imag(other.imag) {}

Complex &Complex::operator+=(const Complex &other) {
    real += other.real;
    imag += other.imag;
    return *this;
}

Complex &Complex::operator-=(const Complex &other) {
    real -= other.real;
    imag -= other.imag;
    return *this;
}

Complex &Complex::operator*=(const Complex &other) {
    Real new_real = (real * other.real) - (imag * other.imag);
    Real new_imag = (real * other.imag) + (imag * other.real);
    real = new_real;
    imag = new_imag;
    return *this;
}

Complex &Complex::operator/=(const Complex &other) {
    Real denom = (other.real * other.real) + (other.imag * other.imag);
    Real new_real = ((real * other.real) + (imag * other.imag)) / denom;
    Real new_imag = ((imag * other.real) - (real * other.imag)) / denom;
    real = new_real;
    imag = new_imag;
    return *this;
}

Complex Complex::operator+(const Complex &other) const {
    return Complex(real + other.real, imag + other.imag);
}

Complex Complex::operator-(const Complex &other) const {
    return Complex(real - other.real, imag - other.imag);
}

Complex Complex::operator*(const Complex &other) const {
    return Complex((real * other.real) - (imag * other.imag),
                   (real * other.imag) + (imag * other.real));
}

Complex Complex::operator/(const Complex &other) const {
    Real denom = (other.real * other.real) + (other.imag * other.imag);
    return Complex(((real * other.real) + (imag * other.imag)) / denom,
                   ((imag * other.real) - (real * other.imag)) / denom);
}

Complex::~Complex() {}

bool Complex::operator==(const Complex &other) const {
    return real == other.real && imag == other.imag;
}

bool Complex::operator>(const Complex &other) const {
    return mag2() > other.mag2();
}

bool Complex::operator<(const Complex &other) const {
    return mag2() < other.mag2();
}

bool Complex::operator>=(const Complex &other) const {
    return mag2() >= other.mag2();
}

bool Complex::operator<=(const Complex &other) const {
    return mag2() <= other.mag2();
}

bool Complex::operator!=(const Complex &other) const {
    return real != other.real || imag != other.imag;
}

Complex Complex::operator-() const {
    Complex temp;
    temp.real = -real;
    temp.imag = -imag;
    return temp;
}

std::string Complex::toString() const {
    return real.toString(10) + (imag >= RealZero ? " + " : " - ") +
           imag.toString(10) + "i";
}

std::istream &Cmm::operator>>(std::istream &stream, Complex &c) {
    Real r, i;
    char sign, i_char;
    stream >> r >> sign >> i >> i_char;
    if (i_char == 'i') {
        if (sign == '-') i = -i;
        c = Complex(r, i);
    } else {
        stream.setstate(std::ios::failbit);
    }
    return stream;
}

std::ostream &Cmm::operator<<(std::ostream &stream, const Complex &c) {
    stream << c.toString();
    return stream;
}

Complex::Complex(Complex &&other) noexcept : real(std::move(other.real)), imag(std::move(other.imag)) {}

Complex::Complex(const Integer &other) {
    real = other;
    imag = 0.0;
}

Complex::Complex(const Real &other) {
    real = other;
    imag = 0.0;
}

Complex &Complex::operator=(Complex &&other) noexcept {
    real = std::move(other.real);
    imag = std::move(other.imag);
    return *this;
}

Real & Complex::getRealPart() {
    return real;
}

Real & Complex::getImagPart() {
    return imag;
}

Real Complex::mag2() const {
    return real * real + imag * imag;
}

Complex &Complex::operator=(const Complex &other) noexcept {
    real = other.real;
    imag = other.imag;
    return *this;
}
