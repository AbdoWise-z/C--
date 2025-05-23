
#ifndef STRING_UTILS_HPP
#define STRING_UTILS_HPP

#include <string>
#include <sstream>
#include <vector>

namespace StringUtils {
    template <typename InputIt>
    std::string join(InputIt begin, InputIt end, const std::string& delimiter = ", ") {
        std::ostringstream oss;
        if (begin != end) {
            oss << *begin++;  // First element (no leading delimiter)
            while (begin != end) {
                oss << delimiter << *begin++;
            }
        }
        return oss.str();
    }

    inline std::string limit(std::string other, int size) {
        if (other.size() > size) {
            return other.substr(0, size);
        }

        return other;
    }

    std::string unescapeString(const std::string& input);
    std::string escapeString(const std::string &input);

    std::vector<std::string> splitLines(const std::string &input);
}



#endif //STRING_UTILS_HPP
