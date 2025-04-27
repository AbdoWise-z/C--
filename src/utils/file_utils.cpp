//
// Created by xabdomo on 4/27/25.
//

#include "file_utils.hpp"
#include <filesystem>
#include <fstream>

namespace fs = std::filesystem;

bool FileUtils::writeContent(const std::string &path, const std::string &content) {
    if (!fs::exists(fs::path(path).parent_path())) {
        if (!fs::create_directory(fs::path(path).parent_path())) return false;
    }

    std::ofstream output(path);
    if (!output.is_open()) {
        return false;
    }

    output << content;
    output.close();
    return true;
}
