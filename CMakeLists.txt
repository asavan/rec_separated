cmake_minimum_required(VERSION 3.19)
project(REC_complex)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_DISABLE_PRECOMPILE_HEADERS ON)
add_compile_options(/W4 /WX /MT)

ADD_SUBDIRECTORY(Codec)
ADD_SUBDIRECTORY(Database)

ADD_SUBDIRECTORY(Settings)
ADD_SUBDIRECTORY(Console_db_editor)

ADD_SUBDIRECTORY(Checker)
ADD_SUBDIRECTORY(Examen)
