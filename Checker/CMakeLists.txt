cmake_minimum_required(VERSION 2.6)
project(checker)

SET(CHECKER_SRC 
	Reader.cpp
	Reader.h
	REC_Reader.cpp
	REC_reader.rc
	resource.h
)

ADD_EXECUTABLE( checker WIN32 ${CHECKER_SRC})
TARGET_LINK_LIBRARIES(checker database-st codec-st settings-st)