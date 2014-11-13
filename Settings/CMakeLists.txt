cmake_minimum_required(VERSION 2.6)
project(settings)

SET(SETTINGS_SRC 
	Settings.cpp
	Settings.h
)
ADD_LIBRARY(settings-st STATIC ${SETTINGS_SRC})