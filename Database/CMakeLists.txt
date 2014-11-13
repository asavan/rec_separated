cmake_minimum_required(VERSION 2.6)
project(db)

SET(DATABASE_SRC 
	Database.cpp
	Database.h
)

ADD_LIBRARY(database-st STATIC ${DATABASE_SRC})
