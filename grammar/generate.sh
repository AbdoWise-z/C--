#!/bin/bash

# Save the current working directory
ORIGINAL_PWD=$(pwd)
cd "$(dirname "$0")"

# Set file names
BISON_FILE="parser.ypp"
LEXER_FILE="lexer.l"

# Check if Bison file exists
if [ ! -f "$BISON_FILE" ]; then
    echo "Error: Bison file '$BISON_FILE' not found."
    exit 1
fi

# Check if Lexer file exists
if [ ! -f "$LEXER_FILE" ]; then
    echo "Error: Lexer file '$LEXER_FILE' not found."
    exit 1
fi

# Generate Bison files
echo "Generating Bison files..."
bison -d "$BISON_FILE" --output="parser.tab.cpp" --header="parser.tab.hpp"
if [ $? -ne 0 ]; then
    echo "Error: Failed to generate Bison files."
    exit 1
fi

# Generate Lexer files
echo "Generating Lexer files..."
flex -o lexer.yy.cpp "$LEXER_FILE"
if [ $? -ne 0 ]; then
    echo "Error: Failed to generate Lexer files."
    exit 1
fi

echo "Generation completed successfully."
cd $ORIGINAL_PWD