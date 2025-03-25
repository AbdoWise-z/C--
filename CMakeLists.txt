cmake_minimum_required(VERSION 3.28)
project(Compilers)

set(CMAKE_CXX_STANDARD 23)

set(CMAKE_C_COMPILER "${CMAKE_CXX_COMPILER}")

file(GLOB PARSER_SRC "${CMAKE_SOURCE_DIR}/grammar/*.c")
file(GLOB PARSER_HDR "${CMAKE_SOURCE_DIR}/grammar/*.h")



message("Sources: " ${PARSER_SRC})
message("Headers: " ${PARSER_HDR})

add_executable(
        Cmm
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

        ${PARSER_HDR}
        ${PARSER_SRC}
)

add_custom_command(
        TARGET Cmm
        PRE_BUILD
        COMMAND ${CMAKE_SOURCE_DIR}/grammar/gen_sources.sh
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        COMMENT "Executing pre-build steps"
)

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
)

target_link_libraries(
        Sandbox
        gmp
)

target_link_libraries(
        Cmm
        gmp
)