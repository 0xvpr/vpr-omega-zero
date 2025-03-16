add_executable(
    ${PROJECT_NAME}
    main.c
    elf.c
    filetypes.c
    pe32.c
    util.c )

set_target_properties(
    ${PROJECT_NAME}
    PROPERTIES
        PREFIX vpr-
)

add_compile_definitions(
    VERSION_MAJOR=${PROJECT_VERSION_MAJOR}
    VERSION_MINOR=${PROJECT_VERSION_MINOR}
    VERSION_PATCH=${PROJECT_VERSION_PATCH}
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
    DESTINATION ${CMAKE_INSTALL_PREFIX}/bin )
