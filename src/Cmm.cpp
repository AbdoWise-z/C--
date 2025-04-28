#include <iostream>
#include <string>

// ========== must have these includes before including parser.tab ==========
#include <filesystem>
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
#include "generator/quad_generator.hpp"
#include "utils/cli.hpp"
#include "utils/file_utils.hpp"
#include "utils/konsol.hpp"
#include "utils/string_utils.hpp"

extern void yylex_destroy();

void run_code(std::vector<std::string> params) {
    try {
        std::string input = StringUtils::join(params.begin(), params.end(), " ");
        auto [code, load] = Cmm::PreProcessor::processContent(input, {"./Cmm/std" , "./std" , "."});

        // std::cout << code << std::endl;

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
    std::cout << std::setw(30) << std::left << color("  --quads", GREEN_FG) << " : Specify output file to write quads. ignored if --interactive is set." << std::endl;
    std::cout << std::setw(30) << std::left << color("  --symbols", GREEN_FG) << " : Specify output file to write symbols. ignored if --interactive is set." << std::endl;

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

    std::string wrapper_code = "#include <" + file_path + ">"; // code injection :goose:

    auto m_path = FileUtils::getSelfPath();
    m_path = std::filesystem::path(m_path).parent_path().string();

    auto paths = {
        m_path + "/..",
        m_path + "/../Cmm",
        m_path + "/../Cmm/std" ,
        m_path + "/Cmm/std" ,
        m_path + "/std" ,
        m_path, include_path
    };

    // std::cout << m_path << std::endl;
    auto [code, load] = Cmm::PreProcessor::processContent(
        wrapper_code, paths
    );

    // std::cout << code << std::endl;
    for (const auto& lib: load) {
        Cmm::NativeLoader::LoadNative(lib);
    }

    Cmm::debugger::exec(code);

    yylex_destroy();

    Cmm::debugger::endSession();
}

static std::vector<std::string> splitLines(const std::string &input) {
    std::vector<std::string> lines;
    std::istringstream stream(input);
    std::string line;
    while (std::getline(stream, line)) {
        lines.push_back(line);
    }
    return lines;
}

void compile_code(const std::string& file_path, const std::string& include_path, const std::string& quads, const std::string& symbols) {
    std::ios::sync_with_stdio(false);
    yydebug = 0;

    std::string wrapper_code = "#include <" + file_path + ">";

    try {
        auto m_path = FileUtils::getSelfPath();
        m_path = std::filesystem::path(m_path).parent_path().string();

        auto paths = {
            m_path + "/..",
            m_path + "/../Cmm",
            m_path + "/../Cmm/std" ,
            m_path + "/Cmm/std" ,
            m_path + "/std" ,
            m_path, include_path
        };

        // std::cout << m_path << std::endl;
        auto [code, load] = Cmm::PreProcessor::processContent(
            wrapper_code, paths
        );

        // auto lines = splitLines(code);
        // for (int i = 0; i < lines.size(); ++i) {
        //     std::cout << std::setw(8) << std::left << std::to_string(i + 1) << lines[i] << std::endl;
        // }
        // for (const auto& lib: load) {
        //     Cmm::NativeLoader::LoadNative(lib);
        // }

        auto program = Cmm::debugger::compileCode(code);
        if (program) {
            auto ok = Cmm::QuadGenerator::generate(program, quads);
            if (!ok) std::cerr << "Failed to generate quads" << std::endl;
            else {

                // std::cout << bcolor("Warns:", CYAN_BG) << std::endl;
                for (const auto& warn: ok->warnings) {
                    std::cout << "[Warn]" << " " << std::to_string(warn.line) << " " << warn.exception << std::endl;
                }

                // if (ok->warnings.empty()) std::cout << "  None" << std::endl;

                // std::cout << bcolor("Errors:", RED_BG) << std::endl;
                for (const auto& err: ok->errors) {
                    std::cout << "[Error]" << " " << std::to_string(err.line) << " " << err.exception << std::endl;
                }

                // if (ok->errors.empty()) std::cout << "  None" << std::endl;

                std::cout << "Generated: " << quads << std::endl;

                // symbol table
                if (!symbols.empty()) {
                    std::stringstream ss;
                    ss << "|" << std::setw(30) << std::left << "Name"
                           << "|" << std::setw(30) << std::left << "Value Type"
                           << "|" << std::setw(30) << std::left << "Accept Types"
                           << "|" << std::setw(30) << std::left << "Value"
                           << "|" << std::setw(20) << std::left << "Code Line"
                           << "|" << std::setw(20) << std::left << "Quad Line"
                           << "|" << std::setw(20) << std::left << "Scope level"
                           << "|" << std::setw(20) << std::left << "Symbol class"
                           << "|" << std::setw(20) << std::left << "Use count"
                           << "|" << std::endl;

                    for (const auto& sym: ok->symbolTable) {
                        ss << "|" << std::setw(30) << std::left << sym.name
                           << "|" << std::setw(30) << std::left << Cmm::Program::stringfy({"", sym.type})
                           << "|" << std::setw(30) << std::left << Cmm::Program::stringfy({"", sym.accept_type})
                           << "|" << std::setw(30) << std::left << sym.value
                           << "|" << std::setw(20) << std::left << sym.codeLine
                           << "|" << std::setw(20) << std::left << sym.quadLine
                           << "|" << std::setw(20) << std::left << sym.scope
                           << "|" << std::setw(20) << std::left << (sym.objectType == Cmm::QuadGenerator::Variable ? "Variable" : "Function")
                           << "|" << std::setw(20) << std::left << sym.useCount
                           << "|" << std::endl;
                    }

                    FileUtils::writeContent(symbols, ss.str());
                    std::cout << "Generated: " << symbols << std::endl;
                }
            }
        }
    } catch (std::exception& e) {
        std::cout << "[Error]" << " " << 1 << " " << e.what() << std::endl;
    }
    yylex_destroy();
}

int main(int argc, char** argv) {
    CommandLineParser clp;

    clp.addArgument("interactive", CommandLineParser::Type::BOOL, true, false);
    clp.addArgument("help", CommandLineParser::Type::BOOL, true, false);

    clp.addArgument("d", CommandLineParser::Type::BOOL, true, false);
    clp.addArgument("debug", CommandLineParser::Type::BOOL, true, false);

    clp.addArgument("I", CommandLineParser::Type::STRING, true, ".");
    clp.addArgument("file", CommandLineParser::Type::STRING, true, "");
    clp.addArgument("quads", CommandLineParser::Type::STRING, true, "");
    clp.addArgument("symbols", CommandLineParser::Type::STRING, true, "");

    try {
        clp.parse(argc, argv);


        auto interactive = clp.get<bool>("interactive");
        auto help = clp.get<bool>("help");
        auto debug = clp.get<bool>("debug") || clp.get<bool>("d");

        auto include_paths = clp.get<std::string>("I");
        auto file = clp.get<std::string>("file");
        auto quads = clp.get<std::string>("quads");
        auto symbols = clp.get<std::string>("symbols");

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

            if (!quads.empty() || !symbols.empty()) {
                compile_code(file, include_paths, quads, symbols);
            } else {
                run_code(file, include_paths);
            }
        }

    } catch (const std::exception& e) {
        std::cerr << "c--: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}