cmake_minimum_required(VERSION 3.28)
project(Compilers)

set(CMAKE_CXX_STANDARD 23)

set(CMAKE_C_COMPILER "${CMAKE_CXX_COMPILER}")

file(GLOB PARSER_CPP_SRC "${CMAKE_SOURCE_DIR}/grammar/*.cpp")
file(GLOB PARSER_C_SRC   "${CMAKE_SOURCE_DIR}/grammar/*.c")
file(GLOB PARSER_HDR     "${CMAKE_SOURCE_DIR}/grammar/*.hpp")

message("Sources: " ${PARSER_CPP_SRC} ${PARSER_C_SRC})
message("Headers: " ${PARSER_HDR})

add_executable(Cmm
        config.h

        primitives/Integer.cpp
        primitives/Integer.h
        primitives/Real.cpp
        primitives/Real.h
        primitives/Complex.cpp
        primitives/Complex.h
        primitives/Bool.h
        primitives/String.h
        primitives.h

        AST.cpp
        AST.h

        Expressions.cpp
        Expressions.h

        MathHelper.cpp
        MathHelper.h

        Values.cpp
        Values.h

        forward.h

        Program.cpp
        Program.h

        Typing.cpp
        Typing.h

        Control.cpp
        Control.h

        Variables.cpp
        Variables.h

        Functional.cpp
        Functional.h

        editor/NanoEditor.cpp
        editor/NanoEditor.h

        NativeLoader.cpp
        NativeLoader.h

        PreProcessor.cpp
        PreProcessor.h

        ${PARSER_HDR}
        ${PARSER_CPP_SRC}
        ${PARSER_C_SRC}

)

add_custom_target(
        GenerateGrammar ALL
        COMMAND ${CMAKE_SOURCE_DIR}/grammar/generate.sh
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        COMMENT "grammar generation..."
)

add_dependencies(Cmm GenerateGrammar)

add_executable(Sandbox
        sandbox.cpp
        config.h

        primitives/Integer.cpp
        primitives/Integer.h
        primitives/Real.cpp
        primitives/Real.h
        primitives/Complex.cpp
        primitives/Complex.h
        primitives/Bool.h
        primitives/String.h
        primitives.h

        AST.cpp
        AST.h

        MathHelper.cpp
        MathHelper.h
        Values.cpp
        Values.h
        Expressions.cpp
        Expressions.h
        forward.h
        Program.cpp
        Program.h
        Typing.cpp
        Typing.h
        Control.cpp
        Control.h

        editor/NanoEditor.cpp
        editor/NanoEditor.h
        Variables.cpp
        Variables.h
        Functional.cpp
        Functional.h
        common.h
)

add_library(io SHARED
        Cmm/std/cpp/io.cpp
        common.h
        primitives/Integer.cpp
        primitives/Integer.h
        primitives/Real.cpp
        primitives/Real.h
        primitives/Complex.cpp
        primitives/Complex.h
        primitives/Bool.h
        primitives/String.h
        primitives.h

        Values.h
        Values.cpp

        MathHelper.h
        MathHelper.cpp
)

add_library(math SHARED
        Cmm/std/cpp/math.cpp
        common.h
        primitives/Integer.cpp
        primitives/Integer.h
        primitives/Real.cpp
        primitives/Real.h
        primitives/Complex.cpp
        primitives/Complex.h
        primitives/Bool.h
        primitives/String.h
        primitives.h

        Values.h
        Values.cpp

        MathHelper.h
        MathHelper.cpp
)

target_link_libraries(
        io
        gmp mpfr
)

target_link_libraries(
        Sandbox
        gmp mpfr
)

target_link_libraries(
        Cmm
        gmp mpfr
)