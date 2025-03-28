
#include <iostream>
#include <ostream>

#include "primitives/Real.h"
// Example usage
int main() {
    Cmm::Real a = Cmm::Real::rand();
    Cmm::Real b = Cmm::Real::rand();
    std::cout << a << " " << b << " " << (a ^ b) << std::endl;
}
