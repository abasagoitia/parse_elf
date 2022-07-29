cmake_minimum_required(VERSION 3.23.2)

project(
    "Dev Symposium: Unix Persistence: ELF files"
    VERSION 1.0
    DESCRIPTION "Example program for parsing and editing ELF Files"
    LANGUAGES C
)

set(HEADER_FILES include/dev_elf.h)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/build)

add_executable(
    parse_elf 
        src/parse_elf.c
        src/header_prints.c
        src/linked_list.c
        ${HEADER_FILES})

target_include_directories(
    parse_elf 
        PRIVATE 
            include
)

target_compile_options(parse_elf PUBLIC 
"-Wall"
"-g"
)
