cmake_minimum_required(VERSION 3.22)
project(REC_complex CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_DISABLE_PRECOMPILE_HEADERS ON)

if (MSVC)
    add_compile_options(/W4 /WX /MT)
else()
    add_compile_options(-Wall -Wextra -pedantic -Werror)
endif()

ADD_SUBDIRECTORY(Codec)
ADD_SUBDIRECTORY(Database)

ADD_SUBDIRECTORY(Settings)
ADD_SUBDIRECTORY(Console_db_editor)

ADD_SUBDIRECTORY(Checker)
ADD_SUBDIRECTORY(Examen)

set_property(DIRECTORY PROPERTY VS_STARTUP_PROJECT Examen)
