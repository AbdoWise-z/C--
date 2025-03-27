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
        std::cout << "Saved Text:\n" << text;
    } else {
        std::cout << "No text saved.\n";
    }

    return 0;
}