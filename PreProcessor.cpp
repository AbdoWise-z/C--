//
// Created by xabdomo on 3/28/25.
//

#include "PreProcessor.h"

#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <filesystem>
#include <optional>

namespace fs = std::filesystem;

// Helper function to check if a file exists in search paths
static std::optional<std::string> findFile(const std::string& filename, const std::vector<std::string>& searchPaths) {
    for (const auto& path : searchPaths) {
        fs::path filePath = fs::path(path) / filename;
        if (fs::exists(filePath)) {
            return filePath.string();
        }

        if (fs::exists(filePath.string() + ".cmm"))
            return filePath.string() + ".cmm";
    }
    return std::nullopt;
}

// Recursive function to process files
static std::pair<std::string, std::vector<std::string>> processFile(const std::string& inputPath, std::vector<std::string> searchPaths) {
    std::vector<std::string> toBindList;
    std::ostringstream processedContent;

    // Try to locate the file
    auto foundFile = findFile(inputPath, searchPaths);
    if (!foundFile) {
        throw std::runtime_error("File not found: " + inputPath);
    }

    std::ifstream file(*foundFile);
    if (!file) {
        throw std::runtime_error("Failed to open file: " + *foundFile);
    }

    // Add current file directory to search paths
    searchPaths.insert(searchPaths.begin(), fs::path(*foundFile).parent_path().string());

    std::string line;
    while (std::getline(file, line)) {
        if (line.find("import \"") == 0 && line.back() == '"') {
            std::string importPath = line.substr(8, line.size() - 9);
            auto [importedContent, importedToBind] = processFile(importPath, searchPaths);
            processedContent << importedContent;
            toBindList.insert(toBindList.end(), importedToBind.begin(), importedToBind.end());
        } else if (line.find("bind \"") == 0 && line.back() == '"') {
            std::string bindPath = line.substr(6, line.size() - 7);
            auto foundBindFile = findFile(bindPath, searchPaths);
            if (!foundBindFile) {
                throw std::runtime_error("Bind file not found: " + bindPath);
            }
            toBindList.push_back(*foundBindFile);
        } else {
            processedContent << line << '\n';
        }
    }

    return {processedContent.str(), toBindList};
}

static std::pair<std::string, std::vector<std::string>> _processContent(const std::string& input, std::vector<std::string> searchPaths) {
    std::ostringstream processedContent;
    std::vector<std::string> toBindList;

    std::stringstream file(input);

    std::string line;
    while (std::getline(file, line)) {
        if (line.find("import \"") == 0 && line.back() == '"') {
            std::string importPath = line.substr(8, line.size() - 9);
            auto [importedContent, importedToBind] = processFile(importPath, searchPaths);
            processedContent << importedContent;
            toBindList.insert(toBindList.end(), importedToBind.begin(), importedToBind.end());
        } else if (line.find("bind \"") == 0 && line.back() == '"') {
            std::string bindPath = line.substr(6, line.size() - 7);
            auto foundBindFile = findFile(bindPath, searchPaths);
            if (!foundBindFile) {
                throw std::runtime_error("Bind file not found: " + bindPath);
            }
            toBindList.push_back(*foundBindFile);
        } else {
            processedContent << line << '\n';
        }
    }

    return {processedContent.str(), toBindList};
}

std::pair<std::string, std::vector<std::string>> Cmm::PreProcessor::loadFile(const std::string &filename) {
    return processFile(filename, {"."});
}

std::pair<std::string, std::vector<std::string>> Cmm::PreProcessor::loadFile(const std::string &filename,
    const std::vector<std::string> &searchPaths) {
    return processFile(filename, searchPaths);
}

std::pair<std::string, std::vector<std::string>> Cmm::PreProcessor::processContent(const std::string &content,
    const std::vector<std::string> &searchPaths) {
    return _processContent(content, searchPaths);
}
