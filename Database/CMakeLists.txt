project(db)

SET(DATABASE_SRC 
	Database.cpp
	Database.h
)

ADD_LIBRARY(database-st STATIC ${DATABASE_SRC})
