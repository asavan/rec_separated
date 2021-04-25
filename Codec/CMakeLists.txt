project(codec)

SET(CODEC_SRC 
	codec.cpp
	codec.h
	my_time.cpp
	my_time.h
)
ADD_LIBRARY(codec-st STATIC ${CODEC_SRC})
