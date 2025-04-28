
#include "string_utils.hpp"

std::string StringUtils::unescapeString(const std::string &input) {
    std::string output;
    output.reserve(input.size()); // Reserve space for efficiency

    for (size_t i = 0; i < input.length(); ++i) {
        if (input[i] == '\\' && i + 1 < input.length()) {
            switch (input[i + 1]) {
                case 'n': output += '\n'; break; // Newline
                case 't': output += '\t'; break; // Tab
                case 'r': output += '\r'; break; // Carriage return
                case 'b': output += '\b'; break; // Backspace
                case 'f': output += '\f'; break; // Form feed
                case 'v': output += '\v'; break; // Vertical tab
                case 'a': output += '\a'; break; // Alert (bell)
                case '\\': output += '\\'; break; // Backslash
                case '"': output += '"'; break; // Double quote
                case '\'': output += '\''; break; // Single quote
                default: output += input[i + 1]; break; // Unrecognized escape, keep as is
            }
            ++i; // Skip the escaped character
        } else {
            output += input[i];
        }
    }

    return output;
}

std::string StringUtils::escapeString(const std::string &input) {
    std::string output;
    // In the worst case every character becomes two chars (e.g. '\n' → "\\n")
    output.reserve(input.size() * 2);

    for (char ch : input) {
        switch (ch) {
            case '\n': output += "\\n";   break;
            case '\t': output += "\\t";   break;
            case '\r': output += "\\r";   break;
            case '\b': output += "\\b";   break;
            case '\f': output += "\\f";   break;
            case '\v': output += "\\v";   break;
            case '\a': output += "\\a";   break;
            case '\\': output += "\\\\";  break;
            case '\"': output += "\\\"";  break;
            case '\'': output += "\\\'";  break;
            default:
                output += ch;
                break;
        }
    }

    return output;
}
