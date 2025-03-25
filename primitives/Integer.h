//
// Created by xabdomo on 3/24/25.
//

#ifndef INTEGER_H
#define INTEGER_H

#include <string>
#include <gmpxx.h>
#include "../config.h"

namespace Namespace {
    class Integer;
    class Real;
    class Complex;

    class Integer {
    private:
        mpz_t mValue{};
        bool del = true;
    public:
        Integer();
        ~Integer();
        Integer(int i);
        Integer(long i);
        Integer(const char* str);
        Integer(const char* str,int base);
        Integer(const Integer& other);
        Integer(const Complex& other);
        Integer(const Real& other);
        Integer(Integer&& other) noexcept ;

        Integer& operator =(Integer&& other) noexcept ;
        Integer& operator =(const Integer& other) noexcept ;
        Integer& operator +=(const Integer& other);
        Integer& operator -=(const Integer& other);
        Integer& operator /=(const Integer& other);
        Integer& operator *=(const Integer& other);
        Integer& operator %=(const Integer& other);

        Integer operator+ (const Integer& b) const;
        Integer operator- (const Integer& b) const;
        Integer operator/ (const Integer& b) const;
        Integer operator* (const Integer& b) const;
        Integer operator% (const Integer& b) const;

        bool operator> (const Integer& b) const;
        bool operator< (const Integer& b) const;
        bool operator== (const Integer& b) const;
        bool operator!= (const Integer& b) const;
        bool operator>= (const Integer& b) const;
        bool operator<= (const Integer& b) const;

        Integer operator- () const;
        Integer operator^ (const Integer& b) const;
        Integer operator! () const;

        [[nodiscard]] std::string toString(int base) const;

        friend std::ostream &operator<<(std::ostream& stream, const Integer &n);
        friend std::istream &operator>>(std::istream& stream, Integer &n);

        friend Real;
        friend Complex;
    };

    std::ostream &operator<<(std::ostream& stream, const Cmm::Integer &n);
    std::istream &operator>>(std::istream& stream, Cmm::Integer &n);

}




#endif //INTEGER_H
