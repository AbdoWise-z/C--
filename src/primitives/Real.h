
#ifndef REAL_H
#define REAL_H

#include <string>
#include <gmpxx.h>


#include "../config.h"

#define RealZero Real(0.0)

namespace Namespace {
    class Integer;
    class Complex;
    class Real;

    class Real {
    private:
        mpf_t mValue{};
        bool del = true;
    public:
        Real();
        ~Real();
        Real(double i);
        Real(const char* str);
        Real(const char* str,int base);

        Real(const Integer& other);
        Real(const Complex& other);
        Real(const Real& other);
        Real(Real&& other) noexcept ;

        Real& operator =(Real&& other) noexcept ;
        Real& operator =(const Real& other) noexcept ;
        Real& operator +=(const Real& other);
        Real& operator -=(const Real& other);
        Real& operator /=(const Real& other);
        Real& operator *=(const Real& other);

        Real operator+ (const Real& b) const;
        Real operator- (const Real& b) const;
        Real operator/ (const Real& b) const;
        Real operator* (const Real& b) const;
        Real operator^ (const Real& b) const;

        bool operator> (const Real& b) const;
        bool operator< (const Real& b) const;
        bool operator== (const Real& b) const;
        bool operator!= (const Real& b) const;
        bool operator>= (const Real& b) const;
        bool operator<= (const Real& b) const;

        Real operator-() const;

        [[nodiscard]] std::string toString(int base) const;
        [[nodiscard]] Real abs() const;
        [[nodiscard]] Real sqrt() const;

        friend std::ostream &operator<<(std::ostream &stream, const Real &n);
        friend std::istream &operator>>(std::istream& stream, Real &n);

        friend Integer;
        friend Complex;

        static Real rand();
    };

    std::ostream &operator << (std::ostream& stream, const Cmm::Real &n);
    std::istream &operator >> (std::istream& stream, Cmm::Real &n);
} // Namespace



#endif //REAL_H
