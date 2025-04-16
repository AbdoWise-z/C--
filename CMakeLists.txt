cmake_minimum_required(VERSION 3.28)
project(Compilers)

set(CMAKE_CXX_STANDARD 23)

set(CMAKE_C_COMPILER "${CMAKE_CXX_COMPILER}")

file(GLOB PARSER_CPP_SRC "${CMAKE_SOURCE_DIR}/grammar/*.cpp")
file(GLOB PARSER_C_SRC   "${CMAKE_SOURCE_DIR}/grammar/*.c")
file(GLOB PARSER_HDR     "${CMAKE_SOURCE_DIR}/grammar/*.hpp")

message("Sources: " ${PARSER_CPP_SRC} ${PARSER_C_SRC})
message("Headers: " ${PARSER_HDR})


include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_executable(Cmm
        Cmm.cpp

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

        nodes/AST.cpp
        nodes/AST.h

        nodes/Expressions.cpp
        nodes/Expressions.h

        MathHelper.cpp
        MathHelper.h

        Values.cpp
        Values.h

        forward.h

        nodes/Program.cpp
        nodes/Program.h

        nodes/Typing.cpp
        nodes/Typing.h

        nodes/Control.cpp
        nodes/Control.h

        nodes/Variables.cpp
        nodes/Variables.h

        nodes/Functional.cpp
        nodes/Functional.h

        editor/NanoEditor.cpp
        editor/NanoEditor.h

        NativeLoader.cpp
        NativeLoader.h

        PreProcessor.cpp
        PreProcessor.h

        debugger/Core.cpp
        debugger/Core.h

        debugger/Renderer.cpp
        debugger/Renderer.h

        utils/cli.cpp
        utils/cli.hpp

        utils/konsol.cpp
        utils/konsol.hpp

        utils/clp.hpp

        grammar/Store.cpp
        grammar/Store.h

        utils/string_utils.cpp
        utils/string_utils.hpp


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

add_library(str SHARED
        Cmm/std/cpp/str.cpp
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

add_library(time SHARED
        Cmm/std/cpp/time.cpp
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

add_library(system SHARED
        Cmm/std/cpp/system.cpp
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
        math
        gmp mpfr
)

target_link_libraries(
        str
        gmp mpfr
)

target_link_libraries(
        time
        gmp mpfr
)

target_link_libraries(
        system
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