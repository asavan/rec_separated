cmake_minimum_required(VERSION 2.6)
project(REC_complex)

##############################################################################
#
# GLOBAL VARIABLES
#SET(CMAKE_GENERATOR "Visual Studio 9 2008")
#SET(CMAKE_CXX_COMPILER msvc)
#SET(CMAKE_MAKE_PROGRAM "Visual Studio 9 2008")

SET(CMAKE_INSTALL_PREFIX "./bin")
#SET(CMAKE_EXE_LINKER_FLAGS "-MT")
#SET(CMAKE_CXX_FLAGS "-MT")
#SET(CMAKE_CXX_FLAGS "-Wall -O3 -funroll-loops -Wno-long-long -Wno-variadic-macros -fPIC")
#SET(CMAKE_C_FLAGS "${CMAKE_CXX_FLAGS}")

##############################################################################
#
# INCLUDE_DIRECTORIES

#INCLUDE_DIRECTORIES(include)

#include_directories(${CMAKE_CURRENT_SOURCE_DIR})
#SET(LIB_PATH ${CMAKE_CURRENT_BINARY_DIR}/lib)
#MESSAGE(STATUS ${LIB_PATH})

#include_directories(${CX_IMAGE_LIB})
###############################################################################
#
# SOURCE_FILES

##############################################################################################
#
# BINARY_FILES
#find_library(CODEC_LIB  	codec-st 	${LIB_PATH})
#find_library(DATABASE_LIB  	database-st ${LIB_PATH})
add_definitions(/MT)

#

ADD_SUBDIRECTORY( Codec				)


ADD_SUBDIRECTORY( Database			)

ADD_SUBDIRECTORY( Settings 			)
ADD_SUBDIRECTORY( Console_db_editor	)

ADD_SUBDIRECTORY( Checker			)
ADD_SUBDIRECTORY( Examen			)
#SET(EXEC plugin  iconsmerge helper)
#ADD_SUBDIRECTORY(resource lib)

                

###############################################################################
# FIND_LIBRARIES



#################################################################################################
#
# INSTALL_RULES
#INSTALL(TARGETS ${EXEC}  DESTINATION lib)
