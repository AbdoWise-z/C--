
#include "NativeLoader.h"
#include <dlfcn.h>
#include <iostream>

#include "nodes/Program.h"
#ifdef _WIN32
#include <windows.h>
#endif


extern "C" {
    void internal_native_insert(const std::string& name, const Cmm::FunctionDefinitionSignature &signature, Cmm::NativeFunction handler) {
        Cmm::Program::createFunction(name, signature, handler);
    }
}

static std::map<std::string, void*> loadedModules;

static bool loadLibraryAndInitialize(const std::string& libPath) {
    auto it = loadedModules.find(libPath);
    if (it != loadedModules.end()) {
        return true;
    }
#ifdef _WIN32
    HINSTANCE handle = LoadLibrary(libPath.c_str());
#else
    void* handle = dlopen(libPath.c_str(), RTLD_LAZY);
#endif

    if (!handle) {
#ifdef CMM_DEBUG
        std::cerr << "Failed to load library: " << dlerror() << std::endl;
#endif
        return false;
    }

    // Define function pointer type
    // typedef void (*InitFunc)(Cmm::NativeAddFunction);

    // Get `init` function pointer
#ifdef _WIN32
    auto init = reinterpret_cast<InitFunc>(GetProcAddress(handle, "init"));
#else
    auto init = reinterpret_cast<Cmm::NativeInitFunction>(dlsym(handle, "init"));
#endif

    if (!init) {
#ifdef CMM_DEBUG
        std::cerr << "Failed to load function `init`: " << dlerror() << std::endl;
#endif
#ifdef _WIN32
        FreeLibrary(handle);
#else
        dlclose(handle);
#endif
        return false;
    }

    init(internal_native_insert);
#ifdef CMM_DEBUG
    std::cout << "Loaded native: " << libPath << std::endl;
#endif

    loadedModules[libPath] = handle;
    return true;
}

void Cmm::NativeLoader::LoadNative(const std::string &path) {
    loadLibraryAndInitialize(path);
}
