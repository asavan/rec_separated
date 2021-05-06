project(examen)
SET(SRC 
	Examination.cpp
	Examination.h  
	questioner.cpp 
)

configure_file(Questioner.rc Questioner.rc COPYONLY)
configure_file(resource.h resource.h COPYONLY)

ADD_CUSTOM_COMMAND(OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/db.rec
	COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/../resource/ ./
	COMMAND cdbe	
	DEPENDS cdbe
)

ADD_EXECUTABLE(Examen WIN32  ${SRC} ${CMAKE_CURRENT_BINARY_DIR}/Questioner.rc ${CMAKE_CURRENT_BINARY_DIR}/resource.h ${CMAKE_CURRENT_BINARY_DIR}/db.rec)

TARGET_LINK_LIBRARIES(Examen database-st codec-st settings-st)
