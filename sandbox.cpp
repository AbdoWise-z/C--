#include <iostream>
#include <gmp.h>

std::string mpfToString(const mpf_t num, int base = 10, size_t digits = 0) {
    if (digits == 0) {
        digits = mpf_get_prec(num) / 3.32;  // Approximate digits from precision
    }

    char *str = (char *)malloc(digits + 10);  // Allocate buffer
    mp_exp_t exponent;  // Exponent value

    mpf_get_str(str, &exponent, base, digits, num);  // Convert number to string

    std::string result = str;  // Convert to std::string
    free(str);  // Free allocated memory

    return result + " * " + std::to_string(base) + "^" + std::to_string(exponent);
}

int main() {
    mpf_t num;
    mpf_init_set_d(num, 123.456);  // Initialize with a value

    std::cout << "Decimal: " << mpfToString(num, 10) << std::endl;
    std::cout << "Binary: " << mpfToString(num, 2) << std::endl;
    std::cout << "Octal: " << mpfToString(num, 8) << std::endl;
    std::cout << "Hexadecimal: " << mpfToString(num, 16) << std::endl;

    mpf_clear(num);  // Free allocated memory
    return 0;
}
