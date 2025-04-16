
#include "Renderer.h"
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>
#include <sys/ioctl.h>
#include <unistd.h>
#include <termios.h>
#include <cstdlib>    // for system("clear")
#include <algorithm>

#include "Core.h"
#include "../nodes/Functional.h"

// ANSI escape codes for colors and cursor control.
#define SELECT_BG "\033[48;5;240m"  // Dark gray background for selected variable.
#define HEADER_BG "\033[41m"        // Red background for stack headers.
#define RESET_COLOR "\033[0m"

#define BLACK_BG   "\033[40m"    // Black background
#define RED_BG     "\033[41m"    // Red background
#define GREEN_BG   "\033[42m"    // Green background
#define YELLOW_BG  "\033[43m"    // Yellow background
#define BLUE_BG    "\033[44m"    // Blue background
#define MAGENTA_BG "\033[45m"    // Magenta background
#define CYAN_BG    "\033[46m"    // Cyan background
#define WHITE_BG   "\033[47m"    // White background
#define RESET_BG   "\033[49m"    // Reset to default background color

#define BLACK_FG   "\033[30m"    // Black text
#define RED_FG     "\033[31m"    // Red text
#define GREEN_FG   "\033[32m"    // Green text
#define YELLOW_FG  "\033[33m"    // Yellow text
#define BLUE_FG    "\033[34m"    // Blue text
#define MAGENTA_FG "\033[35m"    // Magenta text
#define CYAN_FG    "\033[36m"    // Cyan text
#define WHITE_FG   "\033[37m"    // White text
#define RESET_FG   "\033[39m"    // Reset to default text color

#define BRIGHT_BLACK_FG   "\033[90m"  // Bright Black text
#define BRIGHT_RED_FG     "\033[91m"  // Bright Red text
#define BRIGHT_GREEN_FG   "\033[92m"  // Bright Green text
#define BRIGHT_YELLOW_FG  "\033[93m"  // Bright Yellow text
#define BRIGHT_BLUE_FG    "\033[94m"  // Bright Blue text
#define BRIGHT_MAGENTA_FG "\033[95m"  // Bright Magenta text
#define BRIGHT_CYAN_FG    "\033[96m"  // Bright Cyan text
#define BRIGHT_WHITE_FG   "\033[97m"  // Bright White text

#define BRIGHT_BLACK_BG   "\033[100m" // Bright Black background
#define BRIGHT_RED_BG     "\033[101m" // Bright Red background
#define BRIGHT_GREEN_BG   "\033[102m" // Bright Green background
#define BRIGHT_YELLOW_BG  "\033[103m" // Bright Yellow background
#define BRIGHT_BLUE_BG    "\033[104m" // Bright Blue background
#define BRIGHT_MAGENTA_BG "\033[105m" // Bright Magenta background
#define BRIGHT_CYAN_BG    "\033[106m" // Bright Cyan background
#define BRIGHT_WHITE_BG   "\033[107m" // Bright White background

#define BOLD       "\033[1m"    // Bold text
#define UNDERLINE  "\033[4m"    // Underlined text
#define REVERSED   "\033[7m"    // Inverted text
#define RESET_ATTR "\033[0m"    // Reset all attributes (bold, underlined, etc.)

// ANSI codes to hide/show cursor.
#define HIDE_CURSOR "\033[?25l"
#define SHOW_CURSOR "\033[?25h"

// // Data structure for a variable inside a stack frame.
struct Var {
    std::string name;
    std::string type;
    std::string value;
};

// Each stack has a header and a list of variables.
struct stack {
    std::string header;
    std::vector<Var> variables;
};

// Terminal state to restore.
struct termios orig_termios;

// --- Terminal Raw Mode Setup ---
static void enableRawMode() {
    tcgetattr(STDIN_FILENO, &orig_termios);
    struct termios raw = orig_termios;
    raw.c_lflag &= ~(ECHO | ICANON | ISIG); // disable echo, canonical mode, and signals
    tcsetattr(STDIN_FILENO, TCSANOW, &raw);
}

static void disableRawMode() {
    tcsetattr(STDIN_FILENO, TCSANOW, &orig_termios);
}

static void hideCursor() {
    std::cout << HIDE_CURSOR;
}

static void showCursor() {
    std::cout << SHOW_CURSOR;
}

// --- Terminal Dimensions ---
// Returns width (minimum 80 columns).
static int getConsoleWidth() {
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    int totalWidth = w.ws_col;
    return (totalWidth < 80) ? 80 : totalWidth;
}
// Returns height (minimum 20 rows).
static int getConsoleHeight() {
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    int totalHeight = w.ws_row;
    totalHeight = (totalHeight < 20) ? 20 : totalHeight;
    return totalHeight - 1;
}

// --- Helper Function ---
static std::vector<std::string> splitLines(const std::string &str) {
    std::istringstream iss(str);
    std::vector<std::string> lines;
    std::string line;
    while (std::getline(iss, line))
        lines.push_back(line);
    return lines;
}

static std::string getColorForType(std::string type) {
    if (type == "func") {
        return RED_FG;
    }

    if (type == "int") return CYAN_FG;
    if (type == "real") return CYAN_FG;
    if (type == "str") return GREEN_FG;
    if (type == "bool") return YELLOW_FG;
    if (type == "complex") return MAGENTA_FG;

    return RESET_FG;
}

enum class Align {
    LEFT,
    RIGHT,
    CENTER
};

static inline std::string padString(const std::string& input, int width, Align align = Align::LEFT, char fill = ' ') {
    if (static_cast<int>(input.length()) >= width) {
        return input.substr(0, width);  // Truncate if too long
    }

    int padding = width - input.length();

    switch (align) {
        case Align::LEFT:
            return input + std::string(padding, fill);
        case Align::RIGHT:
            return std::string(padding, fill) + input;
        case Align::CENTER:
            int left = padding / 2;
            int right = padding - left;
            return std::string(left, fill) + input + std::string(right, fill);
    }

    return input;  // Fallback
}


// Returns a new string that is rendered with exactly maxWidth columns.
// ANSI escape sequences (starting with "\033[") are copied as-is but do not add to the displayed width.
// Tabs are expanded using tabWidth (default is 4 columns). Control characters (ASCII < 32) are copied but assumed zero width.
std::string limitRenderLength(const std::string &input, int maxWidth, int tabWidth = 4) {
    std::ostringstream oss;
    int rendered = 0;       // current rendered width (in columns)
    size_t i = 0;
    while (i < input.size() && rendered < maxWidth) {
        char c = input[i];
        // Check for an ANSI escape sequence.
        if (c == '\033') { // ESC detected, copy full escape sequence.
            oss << c;
            i++;
            if (i < input.size() && input[i] == '[') {
                oss << input[i];
                i++;
                // ANSI sequence: copy until a letter in the range '@' to '~' appears.
                while (i < input.size() && (input[i] < '@' || input[i] > '~')) {
                    oss << input[i];
                    i++;
                }
                if (i < input.size()) {
                    oss << input[i];
                    i++;
                }
            }
            continue; // do not count escape sequence toward rendered width.
        }
        // Handle tab: Expand to spaces (up to next tab stop).
        if (c == '\t') {
            int spaces = tabWidth - (rendered % tabWidth);
            if (rendered + spaces > maxWidth) {
                spaces = maxWidth - rendered;
            }
            oss << std::string(spaces, ' ');
            rendered += spaces;
            i++;
            continue;
        }
        // For control characters (ASCII < 32), copy them but do not count width.
        if (static_cast<unsigned char>(c) < 32) {
            oss << c;
            i++;
            continue;
        }
        // For any other character, assume it takes one column.
        if (rendered + 1 > maxWidth)
            break;
        oss << c;
        rendered++;
        i++;
    }

    // If the rendered output is shorter than maxWidth, pad with spaces.
    if (rendered < maxWidth) {
        oss << std::string(maxWidth - rendered, ' ');
    }

    return oss.str();
}


// --- Modes ---
// We use two modes: CODE_MODE and STACK_VARIABLE_MODE.
enum Mode { CODE_MODE, STACK_VARIABLE_MODE };

// In STACK_VARIABLE_MODE the header lines are not selectable.
// We remember the last selected variable index per stack so that when re-entering,
// the selection is restored.

// Build the right-pane (stack) view.
// For each stack, output its header (rendered with a red background) and its variable lines.
// Each header is indented by (2 * stack_index) spaces,
// and each variable line is rendered with the same indent plus an additional 3-space indent.
static void buildStackView(const std::vector<stack>& stacks, int paneWidth,
                    std::vector<std::string>& stackViewLines,
                    std::vector<bool>& isHeaderLine,
                    std::vector<int>& stackLineOffsets)
{
    stackViewLines.clear();
    isHeaderLine.clear();
    stackLineOffsets.clear();

    for (size_t i = 0; i < stacks.size(); ++i) {
        auto depth = i;
        if (stacks[0].header == "Native") {
            if (depth > 0) depth--;
        }
        std::string indent(depth * 2, ' ');
        std::string headerLine = indent + stacks[i].header;
        if ((int)headerLine.size() > paneWidth)
            headerLine = headerLine.substr(0, paneWidth);
        // Record header line index.
        stackLineOffsets.push_back(stackViewLines.size());
        stackViewLines.push_back(headerLine);
        isHeaderLine.push_back(true);
        // Render each variable line.
        for (const auto &var : stacks[i].variables) {
            std::string varLine;
            if (var.type.empty())
                varLine = indent
                    + " "
                    + padString(var.name, 14)
                    ;
            else if (var.type != "func")
                varLine =
                    indent
                    + " "
                    + padString(var.name, 14)
                    + ": "
                    + getColorForType(var.type)
                    + padString(var.type, 8)
                    + RESET_FG
                    + "    "
                    + BRIGHT_GREEN_FG
                    + var.value
                ;
            else
                varLine =
                    indent
                    + " "
                    + padString(var.name, 30)
                    + ": "
                    + getColorForType(var.type)
                    + padString(var.type, 8)
                    + RESET_FG
                    + " -> "
                    + BRIGHT_GREEN_FG
                    + var.value
                ;

            stackViewLines.push_back(varLine + RESET_FG);
            isHeaderLine.push_back(false);
        }
    }
}

// --- Redraw Function ---
// Clears the screen using system("clear") and redraws both panes.
static void redraw(const std::vector<std::string>& code_lines,
            const std::vector<stack>& stacks,
            int current_code_line,
            int current_variable_index,
            int current_stack_index,
            Mode mode
            )
{
    int totalWidth = getConsoleWidth();
    int consoleHeight = getConsoleHeight() - 1;
    int dividerWidth = 3; // e.g. " ║ "
    int codeWidth = totalWidth * 0.6;
    if (mode == STACK_VARIABLE_MODE) {
        codeWidth = totalWidth * 0.4;
    }

    int stackWidth = totalWidth - codeWidth - dividerWidth;

    // Build the complete stack view.
    std::vector<std::string> stackViewLines;
    std::vector<bool> isHeaderLine;
    std::vector<int> stackLineOffsets;
    buildStackView(stacks, stackWidth, stackViewLines, isHeaderLine, stackLineOffsets);

    // Compute viewport for the code pane.
    int visibleRows = consoleHeight;
    int codeLinesCount = code_lines.size();
    int code_top = 0;
    if (codeLinesCount > visibleRows) {
        code_top = current_code_line - visibleRows/2;
        if (code_top < 0)
            code_top = 0;
        if (code_top + visibleRows > codeLinesCount)
            code_top = codeLinesCount - visibleRows;
    }

    // In STACK_VARIABLE_MODE, determine the selected variable's line.
    int selected_stack_line = -1;
    if (mode == STACK_VARIABLE_MODE && !stacks[current_stack_index].variables.empty())
    {
        selected_stack_line = stackLineOffsets[current_stack_index] + 1 + current_variable_index;
    }

    // Compute viewport for the stack pane.
    int totalStackLines = stackViewLines.size();
    int stack_top = 0;
    if (totalStackLines > visibleRows) {
        if (selected_stack_line != -1)
            stack_top = selected_stack_line - visibleRows/2;
        else
            stack_top = totalStackLines; // pin to end if not in stack mode

        if (stack_top < 0)
            stack_top = 0;
        if (stack_top + visibleRows > totalStackLines)
            stack_top = totalStackLines - visibleRows;
    }

    // Clear the screen using system("clear").
    auto dummy = system("clear");

    // Divider string.
    std::string divider = " ║ ";

    // Draw each row.
    for (int row = 0; row < visibleRows; ++row) {
        std::string codeSegment, stackSegment;

        // --- Code pane ---
        int code_index = code_top + row;
        if (code_index < codeLinesCount) {
            std::string line = code_lines[code_index];
            if ((int)line.size() > (codeWidth - 2))
                line = line.substr(0, codeWidth - 2);
            std::string plainCode = (code_index == Cmm::debugger::getCurrentLine()) ? ("> " + line) : ("  " + line);

            if (code_index == current_code_line && mode == CODE_MODE)
                codeSegment = std::string(SELECT_BG) + plainCode + RESET_COLOR;
            else
                codeSegment = plainCode;
        } else {
            codeSegment.assign(codeWidth, ' ');
        }

        // --- Stack pane ---
        int stack_index = stack_top + row;
        if (stack_index < totalStackLines) {
            std::string plainStack = stackViewLines[stack_index];

            // Always render header lines with red background.
            if (isHeaderLine[stack_index])
                stackSegment = std::string(HEADER_BG) + plainStack + RESET_COLOR;
            // If in STACK_VARIABLE_MODE and this line is the selected variable, highlight it.
            else if (mode == STACK_VARIABLE_MODE && stack_index == selected_stack_line)
                stackSegment = std::string(SELECT_BG) + plainStack + RESET_COLOR;
            else
                stackSegment = plainStack;
        } else {
            stackSegment.assign(stackWidth, ' ');
        }

        std::cout << limitRenderLength(codeSegment, codeWidth) << divider << limitRenderLength(stackSegment, stackWidth) + RESET_FG << "\n";
    }

    std::cout <<
        BRIGHT_CYAN_FG << UNDERLINE
        << "F7:" << RESET_ATTR << " Step"
        << "\t";

    std::cout <<
       BRIGHT_GREEN_FG << UNDERLINE
       << "F10:" << RESET_ATTR << " Toggle empty"
       << "\t";

    if (Cmm::debugger::isDone()) {
        std::cout << BRIGHT_RED_FG << UNDERLINE
        << "F11:" << RESET_ATTR << " Exit"
        << "\t";
    }

    std::cout << RESET_ATTR;
    std::cout << std::endl;
    std::cout.flush();
}

// --- Input Helper ---
static char readKey() {
    char c;
    ssize_t n = read(STDIN_FILENO, &c, 1);
    if (n < 1)
        return '\0';
    return c;
}

static std::string listTypes(Cmm::Typing::TypeListNode* n) {
    std::stringstream ss;
    int i = 0;
    for (auto t: n->types) {
        i++;
        ss << Cmm::ValuesHelper::ValueTypeAsString(t);
        if (i != n->types.size()) ss << ", ";
    }

    return ss.str();
}

static void buildStack(std::vector<stack>& stacks, bool skip_empty = false) {
    stacks.clear();
    auto program = Cmm::Program::getCurrentProgram();

    if (program.native_functions.size() > 0) {
        stack _stack;
        _stack.header = "Native";

        for (const auto& func: program.native_functions) {

            _stack.variables.push_back({
                .name = Cmm::Program::stringfy(func.first),
                .type = "func",
                .value = "native"
            });
        }

        stacks.push_back(_stack);
    }

    std::string lastName = "Global";
    for (auto& i: program.stack) {
        stack _stack;
        auto name = i.name;
        if (name == "Dummy" && &i != &program.stack[0]) {
            continue;
        }

        if (name != "Dummy") lastName = name;

        if (i.functions.empty() && i.variables.empty()) {
            if (!skip_empty)
                _stack.variables.push_back({
                    .name = "<empty>",
                    .type = "",
                    .value = ""
                });
            else
                continue;
        }

        _stack.header = lastName;

        for (const auto& func: i.functions) {

            _stack.variables.push_back({
                .name = Cmm::Program::stringfy(func.first),
                .type = "func",
                .value = "(" + listTypes(func.second->returnType) + ")"
            });
        }

        for (const auto& var: i.variables) {
            _stack.variables.push_back({
                .name = var.first,
                .type = Cmm::ValuesHelper::ValueTypeAsString(var.second.Value.type),
                .value = Cmm::ValuesHelper::toString(var.second.Value)
            });

            if (_stack.variables[_stack.variables.size() - 1].type == "str") {
                _stack.variables[_stack.variables.size() - 1].value = "\"" + _stack.variables[_stack.variables.size() - 1].value + "\"";
            }
        }

        stacks.push_back(_stack);
    }
}

// --- Interactive Loop ---
// Navigation behavior:
//   - In CODE_MODE: Up/Down move the highlighted code line.
//   - Right arrow in CODE_MODE enters STACK_VARIABLE_MODE (if the current code line's stack exists and has variables).
//   - In STACK_VARIABLE_MODE:
//       * Up arrow: If not at the top, move up; if at top and previous stack exists, jump to the previous stack and restore its selection.
//       * Down arrow: If not at the bottom, move down; if at bottom and next stack exists, jump to it and restore its selection.
//       * Left arrow returns to CODE_MODE.
// The last selected variable index per stack is remembered so that re-entering the stack returns to the previously selected element.
// Additionally, the following function keys are handled (empty handlers):
//   - F8: Step      (handle with an empty comment)
//   - F9: Step Into (handle with an empty comment)
//   - F10: Continue (handle with an empty comment)
//   - F11: Pause    (handle with an empty comment)
static void interactive_debug_terminal(const std::string &code) {
    std::vector<std::string> code_lines = splitLines(code);

    Mode mode = CODE_MODE;
    int numCodeLines = code_lines.size();
    // Remember the last selected variable index per stack.
    int current_variable_index = 0;
    int current_stack_index = 0;
    int current_code_line = Cmm::debugger::getCurrentLine();
    bool skip_empty_stacks = true;
    std::vector<stack> stacks;

    enableRawMode();
    hideCursor();  // Disable the built-in cursor.
    buildStack(stacks, skip_empty_stacks);
    redraw(code_lines, stacks, current_code_line, current_variable_index, current_stack_index, mode);

    while (true) {
        char c = readKey();
        // Exit if Ctrl+C (ASCII 3) is pressed.
        if (c == '\003')
            break;
        if (c == '\033') { // Escape sequence (for arrow keys & function keys)
            char seq1 = readKey();
            if (seq1 == '[') {
                char seq2 = readKey();
                // First check if we are dealing with a multi-digit sequence (for function keys).
                if (seq2 >= '0' && seq2 <= '9') {
                    std::string number;
                    number.push_back(seq2);
                    while (true) {
                        char next = readKey();
                        if (next == '~')
                            break;
                        number.push_back(next);
                    }
                    // Handle function keys based on the numeric code.
                    if (number == "18") {
                        // F8 pressed: Step
                        // [F8 handler goes here]
                        if (!Cmm::debugger::isDone()) {
                            Cmm::debugger::step();
                            current_code_line = Cmm::debugger::getCurrentLine();
                        }
                    } else if (number == "19") {
                        // F8 pressed: Step
                        // [F8 handler goes here]
                    } else if (number == "20") {
                        // F9 pressed: Step Into
                        // [F9 handler goes here]
                    } else if (number == "21") {
                        skip_empty_stacks = !skip_empty_stacks;
                    } else if (number == "23") {
                        if (Cmm::debugger::isDone()) {
                            break;
                        }
                    }
                } else {
                    // Handle standard escape sequences for arrow keys.
                    if (seq2 == 'A') { // Up arrow.
                        if (mode == CODE_MODE) {
                            if (numCodeLines > 0)
                                current_code_line = (current_code_line - 1 + numCodeLines) % numCodeLines;
                        } else if (mode == STACK_VARIABLE_MODE) {
                            int cnt = stacks[current_stack_index].variables.size();
                            if (cnt > 0) {
                                if (current_variable_index > 0) {
                                    current_variable_index--;
                                } else {
                                    if (current_stack_index > 0) current_stack_index--;
                                    current_variable_index = stacks[current_stack_index].variables.size() - 1;
                                }
                            }
                        }
                    } else if (seq2 == 'B') { // Down arrow.
                        if (mode == CODE_MODE) {
                            if (numCodeLines > 0)
                                current_code_line = (current_code_line + 1) % numCodeLines;
                        } else if (mode == STACK_VARIABLE_MODE) {
                            int cnt = stacks[current_stack_index].variables.size();
                            if (cnt > 0) {
                                if (current_variable_index < cnt - 1) {
                                    current_variable_index++;
                                } else {
                                    // At bottom of current stack: if next stack exists, jump to it.
                                    if (current_stack_index < stacks.size() - 1) {
                                        current_stack_index++;
                                        current_variable_index = 0;
                                    }
                                }
                            }
                        }
                    } else if (seq2 == 'C') { // Right arrow.
                        if (mode == CODE_MODE) {
                            mode = STACK_VARIABLE_MODE;
                        }
                    } else if (seq2 == 'D') { // Left arrow.
                        if (mode == STACK_VARIABLE_MODE) {
                            mode = CODE_MODE;
                        }
                    }
                }
            }
        } else if (c == 'q') {
            break;
        }
        buildStack(stacks, skip_empty_stacks);
        redraw(code_lines, stacks, current_code_line, current_variable_index, current_stack_index, mode);
    }

    system("clear");
    showCursor();
    disableRawMode();
}


void Cmm::debugger::launch() {
    interactive_debug_terminal(getCode());
}
