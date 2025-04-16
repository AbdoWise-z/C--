
#ifndef CLI_HPP
#define CLI_HPP

#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <unordered_map>
#include <functional>
#include <algorithm>

class CommandLineInterface {
public:
    // The command handler function type.
    using CmdHandler = std::function<void(const std::vector<std::string>&)>;

    // Constructor receives a fallback handler that is called if no command matches.
    explicit CommandLineInterface(CmdHandler fallbackFunction);

    // Add a command mapping
    void addCommand(const std::string &command, CmdHandler handler);

    // Start the CLI loop. It continuously reads input until exit is called.
    void run();

    // Alternative to calling "exit" from inside a command handler.
    void exit();

    void setPrompt(const std::string &prompt);

private:
    std::unordered_map<std::string, CmdHandler> commands;
    CmdHandler fallback;
    std::string prompt = ">>> ";
    bool running;
};

#endif //CLI_HPP
