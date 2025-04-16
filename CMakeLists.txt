cmake_minimum_required(VERSION 3.28)
project(Compilers)

set(CMAKE_CXX_STANDARD 23)

set(CMAKE_C_COMPILER "${CMAKE_CXX_COMPILER}")

file(GLOB PARSER_CPP_SRC "${CMAKE_SOURCE_DIR}/src/grammar/*.cpp")
file(GLOB PARSER_C_SRC   "${CMAKE_SOURCE_DIR}/src/grammar/*.c")
file(GLOB PARSER_HDR     "${CMAKE_SOURCE_DIR}/src/grammar/*.hpp")

message("Sources: " ${PARSER_CPP_SRC} ${PARSER_C_SRC})
message("Headers: " ${PARSER_HDR})


include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)

add_executable(Cmm
        src/Cmm.cpp

        src/config.h

        src/primitives/Integer.cpp
        src/primitives/Integer.h
        src/primitives/Real.cpp
        src/primitives/Real.h
        src/primitives/Complex.cpp
        src/primitives/Complex.h
        src/primitives/Bool.h
        src/primitives/String.h
        src/primitives.h

        src/nodes/AST.cpp
        src/nodes/AST.h

        src/nodes/Expressions.cpp
        src/nodes/Expressions.h

        src/MathHelper.cpp
        src/MathHelper.h

        src/Values.cpp
        src/Values.h

        src/forward.h

        src/nodes/Program.cpp
        src/nodes/Program.h

        src/nodes/Typing.cpp
        src/nodes/Typing.h

        src/nodes/Control.cpp
        src/nodes/Control.h

        src/nodes/Variables.cpp
        src/nodes/Variables.h

        src/nodes/Functional.cpp
        src/nodes/Functional.h

        src/editor/NanoEditor.cpp
        src/editor/NanoEditor.h

        src/NativeLoader.cpp
        src/NativeLoader.h

        src/PreProcessor.cpp
        src/PreProcessor.h

        src/debugger/Core.cpp
        src/debugger/Core.h

        src/debugger/Renderer.cpp
        src/debugger/Renderer.h

        src/utils/cli.cpp
        src/utils/cli.hpp

        src/utils/konsol.cpp
        src/utils/konsol.hpp

        src/utils/clp.hpp

        src/grammar/Store.cpp
        src/grammar/Store.h

        src/utils/string_utils.cpp
        src/utils/string_utils.hpp


        ${PARSER_HDR}
        ${PARSER_CPP_SRC}
        ${PARSER_C_SRC}
)

add_custom_target(
        GenerateGrammar ALL
        COMMAND ${CMAKE_SOURCE_DIR}/src/grammar/generate.sh
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        COMMENT "grammar generation..."
)

add_dependencies(Cmm GenerateGrammar)

add_executable(Sandbox
        src/sandbox.cpp
        src/config.h
)

add_library(io SHARED
        Cmm/std/cpp/io.cpp
        src/common.h
        src/primitives/Integer.cpp
        src/primitives/Integer.h
        src/primitives/Real.cpp
        src/primitives/Real.h
        src/primitives/Complex.cpp
        src/primitives/Complex.h
        src/primitives/Bool.h
        src/primitives/String.h
        src/primitives.h

        src/Values.h
        src/Values.cpp

        src/MathHelper.h
        src/MathHelper.cpp
)

add_library(math SHARED
        Cmm/std/cpp/math.cpp
        src/common.h
        src/primitives/Integer.cpp
        src/primitives/Integer.h
        src/primitives/Real.cpp
        src/primitives/Real.h
        src/primitives/Complex.cpp
        src/primitives/Complex.h
        src/primitives/Bool.h
        src/primitives/String.h
        src/primitives.h

        src/Values.h
        src/Values.cpp

        src/MathHelper.h
        src/MathHelper.cpp
)

add_library(str SHARED
        Cmm/std/cpp/str.cpp
        src/common.h
        src/primitives/Integer.cpp
        src/primitives/Integer.h
        src/primitives/Real.cpp
        src/primitives/Real.h
        src/primitives/Complex.cpp
        src/primitives/Complex.h
        src/primitives/Bool.h
        src/primitives/String.h
        src/primitives.h

        src/Values.h
        src/Values.cpp

        src/MathHelper.h
        src/MathHelper.cpp
)

add_library(time SHARED
        Cmm/std/cpp/time.cpp
        src/common.h
        src/primitives/Integer.cpp
        src/primitives/Integer.h
        src/primitives/Real.cpp
        src/primitives/Real.h
        src/primitives/Complex.cpp
        src/primitives/Complex.h
        src/primitives/Bool.h
        src/primitives/String.h
        src/primitives.h

        src/Values.h
        src/Values.cpp

        src/MathHelper.h
        src/MathHelper.cpp
)

add_library(system SHARED
        Cmm/std/cpp/system.cpp
        src/common.h
        src/primitives/Integer.cpp
        src/primitives/Integer.h
        src/primitives/Real.cpp
        src/primitives/Real.h
        src/primitives/Complex.cpp
        src/primitives/Complex.h
        src/primitives/Bool.h
        src/primitives/String.h
        src/primitives.h

        src/Values.h
        src/Values.cpp

        src/MathHelper.h
        src/MathHelper.cpp
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