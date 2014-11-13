cmake_minimum_required(VERSION 2.6)
project(db_editor)

SET(SRC 
	main.cpp
)
ADD_EXECUTABLE(cdbe ${SRC})
TARGET_LINK_LIBRARIES(cdbe database-st codec-st settings-st)