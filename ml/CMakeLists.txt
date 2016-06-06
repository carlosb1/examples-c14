cmake_minimum_required (VERSION 2.8)
project (Tracker)
set(CMAKE_VERBOSE_MAKEFILE 1)



include_directories ("../")
include_directories ("./include")

#Add flags
#Debug flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -std=c++1y -DNDEBUG -DCMAKE_BUILD_TYPE=Release -DBENCHMARK_ENABLE_LTO=true")
# Target system
set( SRCFILES
	./algorithms/multithread_client_search.cpp
	
	)

add_executable(test ${SRCFILES} )
#TODO Add find_library for each  link
#target_link_libraries (test gtest gmock pthread )
target_link_libraries (test benchmark pthread )
