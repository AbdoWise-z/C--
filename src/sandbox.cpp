#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>
#include <sys/ioctl.h>
#include <unistd.h>
#include <termios.h>
#include <cstdlib>
#include <algorithm>

int main() {
    int i = 0;
    for (int i = 0;i < 5;i++) {
        std::cout << "hmm" << std::endl;
    }

    std::cout << i << std::endl;
}
