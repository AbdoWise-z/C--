#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <unistd.h>

#include "editor/NanoEditor.h"

// Example usage
int main() {
    std::string text = NanoEditor::edit();
    
    if (!text.empty()) {
        std::cout << "\nSaved Text:\n" << text;
    } else {
        std::cout << "\nNo text saved.\n";
    }

    return 0;
}