#include <iostream>
#include <string>

// ========== must have these includes before including parser.tab ==========
#include <iomanip>

#include "config.h"
#include "forward.h"
#include "nodes/AST.h"
#include "primitives.h"
#include "MathHelper.h"
#include "Values.h"
#include "nodes/Expressions.h"
#include "nodes/Program.h"

#include "grammar/parser.tab.hpp"

#include "utils/clp.hpp"
#include "NativeLoader.h"
#include "PreProcessor.h"
#include "debugger/Core.h"
#include "debugger/Renderer.h"
#include "editor/NanoEditor.h"
#include "utils/cli.hpp"
#include "utils/konsol.hpp"
#include "utils/string_utils.hpp"

extern void yylex_destroy();

void run_code(std::vector<std::string> params) {
    try {
        std::string input = StringUtils::join(params.begin(), params.end(), " ");
        auto [code, load] = Cmm::PreProcessor::processContent(input, {"./Cmm/std" , "./std" , "."});

        for (auto& lib : load) {
            Cmm::NativeLoader::LoadNative(lib);
        }

        Cmm::debugger::exec(code);
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
}

void cmd_debugger(std::vector<std::string> params) {
    if (params.size() > 1) {
        std::cout << "Usage: debugger [enable/disable]" << std::endl;
        return;
    }

    if (params.size() == 1) {
        const auto& param = params[0];
        if (param == "enable") {
            Cmm::debugger::enableDebugger();
        } else if (param == "disable") {
            Cmm::debugger::disableDebugger();
        } else {
            std::cout << "Usage: debugger [enable/disable]" << std::endl;
        }
    } else {
        Cmm::debugger::launch();
    }
}

void cmd_editor(std::vector<std::string> params) {
    if (params.size() > 0) {
        std::cout << "Usage: editor" << std::endl;
        return;
    }

    run_code({ NanoEditor::edit() });
}

void run_interactive() {

    CommandLineInterface cli(run_code);
    cli.setPrompt(">>> ");
    cli.addCommand("debugger", cmd_debugger);
    cli.addCommand("editor", cmd_editor);

    std::ios::sync_with_stdio(false);
    yydebug = 0;

    std::string input;
    std::cout << "Copyright © 2025 xAbdoMo et al. All rights reserved." << std::endl;
    std::cout << "Unauthorized copying, reproduction, or distribution of this software is strictly prohibited." << std::endl;
    std::cout << "Type 'editor' to open code editor, 'exit' to exit, 'help' for a list of commands, or any Cmm \n"
                 "statement to execute." << std::endl;

    Cmm::debugger::beginSession();

    cli.run();

    yylex_destroy();
    Cmm::debugger::endSession();
}

void print_help() {
    std::cout << "This is " << color("C--" , YELLOW_FG) << " help page (minus minus cuz it's a down grade)" << std::endl;
    std::cout << bcolor("Supported arguments:", RED_BG) << std::endl;

    std::cout << std::setw(30) << std::left << color("  --interactive", GREEN_FG) << " : Runs the compiler on interactive mode, In this mode you can use extra" << std::endl;
    std::cout << "set of commands (at the button of this page) and also run expressions in the C-- language." << std::endl;

    std::cout << std::setw(30) << std::left << color("  --help", GREEN_FG) << " : shows this page" << std::endl;

    std::cout << std::setw(30) << std::left << color("  --d / --debug", GREEN_FG) << " : Run in debugging mode, enable stepping and stack view (experimental)." << std::endl;

    std::cout << std::setw(30) << std::left << color("  --file", GREEN_FG) << " : Specify input file to compile / run. ignored if --interactive is set." << std::endl;
    std::cout << std::setw(30) << std::left << color("  --I", GREEN_FG) << " : Specify include path for the compiler to search for files." << std::endl;

    std::cout << bcolor("Interactive mode commands:", RED_BG) << std::endl;

    std::cout << std::setw(36) << std::left << color("  editor", BLUE_FG) << " : Opens the built-in editor window to type code in." << std::endl;
    std::cout << std::setw(36) << std::left << color("  debugger [enable/disable]", BLUE_FG) << " : Set the debugger to enabled or disabled mode." << std::endl;
    std::cout << std::setw(36) << std::left << color("  exit", BLUE_FG) << " : Exists." << std::endl;
    std::cout << std::setw(36) << std::left << color("  debugger", BLUE_FG) << " : Launch the debugger (show current global memory)." << std::endl;

    std::cout << std::endl;
    std::cout << "And that's it for the help page .. please notice that features such as " << color("debugger", RED_FG) << std::endl <<
        "are experimental." << std::endl;

    std::cout << std::endl;
}

void run_code(const std::string& file_path, const std::string& include_path) {

    std::ios::sync_with_stdio(false);
    yydebug = 0;

    Cmm::debugger::beginSession();

    std::string wrapper_code = "#import \"" + file_path + "\""; // yes this works ..
    auto [code, load] = Cmm::PreProcessor::processContent(
        wrapper_code,
        {"./Cmm/std" , "./std" , ".", include_path}
        );

    for (const auto& lib: load) {
        Cmm::NativeLoader::LoadNative(lib);
    }

    Cmm::debugger::exec(code);

    yylex_destroy();

    Cmm::debugger::endSession();
}

int main(int argc, char** argv) {
    CommandLineParser clp;

    clp.addArgument("interactive", CommandLineParser::Type::BOOL, true, false);
    clp.addArgument("help", CommandLineParser::Type::BOOL, true, false);

    clp.addArgument("d", CommandLineParser::Type::BOOL, true, false);
    clp.addArgument("debug", CommandLineParser::Type::BOOL, true, false);

    clp.addArgument("I", CommandLineParser::Type::STRING, true, ".");
    clp.addArgument("file", CommandLineParser::Type::STRING, true, "");

    try {
        clp.parse(argc, argv);


        auto interactive = clp.get<bool>("interactive");
        auto help = clp.get<bool>("help");
        auto debug = clp.get<bool>("debug") || clp.get<bool>("d");

        auto include_paths = clp.get<std::string>("I");
        auto file = clp.get<std::string>("file");

        if (debug) {
            Cmm::debugger::enableDebugger();
        }

        if (help) {
            print_help();
        }

        if (interactive) {
            run_interactive();
        } else {
            if (file.empty()) {
                std::cerr << "c--: " << color("fatal error:", RED_FG) << " no input files" << std::endl;
                std::cerr << "Run with \"Cmm --help\" for a list of commands" << std::endl;
                return -1;
            }

            run_code(file, include_paths);
        }

    } catch (const std::exception& e) {
        std::cerr << "c--: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}