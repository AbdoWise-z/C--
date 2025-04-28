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

#if defined(_WIN32)
  #include <windows.h>
  static std::string getExecutablePath() {
    char buf[MAX_PATH];
    DWORD len = ::GetModuleFileNameA(NULL, buf, MAX_PATH);
    if (len == 0 || len == MAX_PATH) throw std::runtime_error("GetModuleFileName failed");
    return {buf, (size_t)len};
  }
#elif defined(__APPLE__)
  #include <mach-o/dyld.h>
  #include <limits.h>
  #include <vector>
  #include <stdlib.h>
  static std::string getExecutablePath() {
    uint32_t size = 0;
    _NSGetExecutablePath(nullptr, &size);
    std::vector<char> buf(size);
    if (_NSGetExecutablePath(buf.data(), &size) != 0) throw std::runtime_error("Buffer too small");
    char realPath[PATH_MAX];
    if (!realpath(buf.data(), realPath)) throw std::runtime_error("realpath failed");
    return realPath;
  }
#elif defined(__linux__)
  #include <unistd.h>
  #include <limits.h>
  static std::string getExecutablePath() {
    char buf[PATH_MAX];
    ssize_t len = ::readlink("/proc/self/exe", buf, sizeof(buf) - 1);
    if (len == -1) throw std::runtime_error("readlink failed");
    buf[len] = '\0';
    return buf;
  }
#else
  #error "Unsupported platform"
#endif

std::string FileUtils::getSelfPath() {
  return getExecutablePath();
}
