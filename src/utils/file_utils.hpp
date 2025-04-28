//
// Created by xabdomo on 4/27/25.
//

#ifndef FILE_UTILS_HPP
#define FILE_UTILS_HPP
#include <string>


namespace FileUtils {
    bool writeContent(const std::string& path, const std::string& content);

    std::string getSelfPath();
};



#endif //FILE_UTILS_HPP
