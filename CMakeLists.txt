cmake_minimum_required( VERSION 3.22 )

project( omega-zero CXX )

set( CMAKE_CXX_STANDARD_REQUIRED ON )
set( CMAKE_CXX_STANDARD 20 )

set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin )

set( INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include )
include_directories( ${PROJECT_NAME} ${INCLUDE_DIR} )

set( SOURCE_DIR ${CMAKE_SOURCE_DIR}/src )
set( SOURCES
    # CXX Sources
    ${SOURCE_DIR}/elf.cpp
    ${SOURCE_DIR}/filetypes.cpp
    ${SOURCE_DIR}/main.cpp
    ${SOURCE_DIR}/parser.cpp
    ${SOURCE_DIR}/pe32.cpp
    ${SOURCE_DIR}/util.cpp
    # CXX Headers
    ${INCLUDE_DIR}/elf.hpp
    ${INCLUDE_DIR}/filetypes.hpp
    ${INCLUDE_DIR}/parser.hpp
    ${INCLUDE_DIR}/pe32.hpp
    ${INCLUDE_DIR}/util.hpp
)

add_executable( ${PROJECT_NAME} ${SOURCES} )
set_target_properties(
    ${PROJECT_NAME}
    PROPERTIES
        PREFIX vpr-
)

target_compile_options(
    ${PROJECT_NAME}
    PRIVATE $<$<C_COMPILER_ID:MSVC>:/W4>
            $<$<C_COMPILER_ID:MSVC>:/O2>
            $<$<C_COMPILER_ID:MSVC>:/DNDEBUG>
            $<$<C_COMPILER_ID:GNU>:-Ofast>
            $<$<C_COMPILER_ID:GNU>:-Wall>
            $<$<C_COMPILER_ID:GNU>:-Wextra>
            $<$<C_COMPILER_ID:GNU>:-Werror>
            $<$<C_COMPILER_ID:GNU>:-Wshadow>
            $<$<C_COMPILER_ID:GNU>:-Wpedantic>
            $<$<C_COMPILER_ID:GNU>:-Wconversion>
            $<$<C_COMPILER_ID:GNU>:-ffunction-sections>
            $<$<C_COMPILER_ID:GNU>:-ffast-math>
            $<$<C_COMPILER_ID:GNU>:-funroll-loops>
            $<$<C_COMPILER_ID:GNU>:-fPIE>
            $<$<C_COMPILER_ID:AppleClang>:-Ofast>
            $<$<C_COMPILER_ID:AppleClang>:-Wall>
            $<$<C_COMPILER_ID:AppleClang>:-Wextra>
            $<$<C_COMPILER_ID:AppleClang>:-Werror>
            $<$<C_COMPILER_ID:AppleClang>:-Wshadow>
            $<$<C_COMPILER_ID:AppleClang>:-Wpedantic>
            $<$<C_COMPILER_ID:AppleClang>:-Wconversion>
            $<$<C_COMPILER_ID:AppleClang>:-ffunction-sections>
            $<$<C_COMPILER_ID:AppleClang>:-ffast-math>
            $<$<C_COMPILER_ID:AppleClang>:-funroll-loops>
            $<$<C_COMPILER_ID:AppleClang>:-fPIE>
)

target_link_options(
    ${PROJECT_NAME}
    PRIVATE $<$<C_COMPILER_ID:MSVC>:/MANIFEST:NO>
            $<$<C_COMPILER_ID:GNU>:-s>
            $<$<C_COMPILER_ID:AppleClang>:-s>
)

install(
    TARGETS     ${PROJECT_NAME}
    DESTINATION ${CMAKE_INSTALL_PREFIX}/bin
)
