cmake_minimum_required (VERSION 2.8)
project (Tracker)
set(CMAKE_VERBOSE_MAKEFILE 1)



include_directories ("./")
include_directories ("./murmurhash3")

#Add flags
#Debug flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -std=c++1z -DNDEBUG -DCMAKE_BUILD_TYPE=Release")
# Target system
set( SRCFILES
	./murmurhash3/MurmurHash3.cpp
	./bloom_filter.cpp
	./test_bloom_filter.cpp
	)

add_executable(test ${SRCFILES} )

#TODO Add find_library for each  link
target_link_libraries (test  pthread )
