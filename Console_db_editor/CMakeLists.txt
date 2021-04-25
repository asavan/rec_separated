project(cdbe)

SET(SRC 
	main.cpp
)
ADD_EXECUTABLE(cdbe ${SRC})
TARGET_LINK_LIBRARIES(cdbe database-st codec-st settings-st)
