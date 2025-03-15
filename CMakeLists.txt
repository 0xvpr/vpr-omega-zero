cmake_minimum_required( VERSION 3.14 FATAL_ERROR )

set( CMAKE_C_STANDARD_REQUIRED ON )
set( CMAKE_C_STANDARD 99 )

set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin )

project( omega-zero
         VERSION     1.1.0
         LANGUAGES   C )

add_subdirectory( omega-zero )
