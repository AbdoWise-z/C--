
#ifndef PREPROCESSOR_H
#define PREPROCESSOR_H

#include <string>
#include <vector>

#include "config.h"


namespace Namespace::PreProcessor {
    std::pair<std::string, std::vector<std::string>> loadFile(const std::string &filename);
    std::pair<std::string, std::vector<std::string>> loadFile(const std::string &filename, const std::vector<std::string> &searchPaths);
    std::pair<std::string, std::vector<std::string>> processContent(const std::string &content, const std::vector<std::string> &searchPaths);

};



#endif //PREPROCESSOR_H
