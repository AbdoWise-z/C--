//
// Created by xabdomo on 3/24/25.
//

#ifndef COMPLEX_H
#define COMPLEX_H

#include "Real.h"
#include "../config.h"

namespace Namespace {
    class Integer;
    class Real;
    class Complex;

    class Complex {
    private:
        Real real;
        Real imag;

    public:
        Complex();
        Complex(const Real &r, const Real &i);
        Complex(double r, double i);
        Complex(const Complex &other);
        Complex(Complex &&other) noexcept;
        Complex(const Integer& other);
        Complex(const Real& other);

        ~Complex();

        Complex &operator=(const Complex &other) noexcept;
        Complex &operator=(Complex &&other) noexcept;

        Real& getRealPart();
        Real& getImagPart();

        Real mag2() const;

        Complex &operator+=(const Complex &other);
        Complex &operator-=(const Complex &other);
        Complex &operator*=(const Complex &other);
        Complex &operator/=(const Complex &other);

        Complex operator+(const Complex &other) const;
        Complex operator-(const Complex &other) const;
        Complex operator*(const Complex &other) const;
        Complex operator/(const Complex &other) const;

        bool operator==(const Complex &other) const;
        bool operator>(const Complex &other) const;
        bool operator<(const Complex &other) const;
        bool operator>=(const Complex &other) const;
        bool operator<=(const Complex &other) const;
        bool operator!=(const Complex &other) const;

        Complex operator- () const;

        [[nodiscard]] std::string toString() const;

        friend std::istream &operator>>(std::istream &stream, Complex &c);
        friend std::ostream &operator<<(std::ostream &stream, const Complex &c);

        friend Integer;
        friend Real;
    };

    std::istream &operator>>(std::istream &stream, Cmm::Complex &c);
    std::ostream &operator<<(std::ostream &stream, const Cmm::Complex &c);
} // Namespace



#endif //COMPLEX_H
