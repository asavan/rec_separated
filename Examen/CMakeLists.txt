cmake_minimum_required(VERSION 2.6)
project(examen)
SET(SRC 
	Examination.cpp
	Examination.h  
	questioner.cpp 
	#Questioner.rc  
	#resource.h 
)   
GET_TARGET_PROPERTY(MY_GENERATOR_EXE cdbe LOCATION)

#ADD_CUSTOM_COMMAND(OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/db.rec
#	COMMAND  ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/../resource/ ./
#	COMMAND  ${MY_GENERATOR_EXE}
	#COMMAND  ${CMAKE_COMMAND} -E copy db.rec  ${CMAKE_CURRENT_SOURCE_DIR}/../resource/db.rec
	#COMMAND  ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/Questioner.rc  ${CMAKE_CURRENT_BINARY_DIR}/Questioner.rc
	#COMMAND cdbe
#	DEPENDS cdbe ${CMAKE_CURRENT_SOURCE_DIR}/../resource/settings.txt
#)

ADD_CUSTOM_COMMAND(OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/Questioner.rc ${CMAKE_CURRENT_BINARY_DIR}/db.rec
	
	COMMAND  ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/../resource/ ./
	COMMAND  ${MY_GENERATOR_EXE}
	
	COMMAND  ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/Questioner.rc  ${CMAKE_CURRENT_BINARY_DIR}/Questioner.rc
	COMMAND  ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/resource.h  ${CMAKE_CURRENT_BINARY_DIR}/resource.h
	DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/Questioner.rc ${CMAKE_CURRENT_SOURCE_DIR}/resource.h cdbe ${CMAKE_CURRENT_SOURCE_DIR}/../resource/settings.txt
)

ADD_CUSTOM_TARGET(examen1 DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/db.rec)

ADD_EXECUTABLE(examen WIN32  ${SRC} ${CMAKE_CURRENT_BINARY_DIR}/Questioner.rc)
ADD_DEPENDENCIES(examen examen1)

TARGET_LINK_LIBRARIES(examen database-st codec-st settings-st)
