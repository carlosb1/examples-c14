cmake_minimum_required (VERSION 2.8)
project (Tracker)
set(CMAKE_VERBOSE_MAKEFILE 1)

#Adding gmock library
# Include directories
#Add test includes
# include_directories ("./gmock-1.7.0/include")
# include_directories ("./gmock-1.7.0/gtest/include")
include_directories ("./include")
# add_subdirectory("./gmock-1.7.0")


#Add flags
#Debug flags
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lssl -lcrypto -pthread -std=c++1y -ggdb")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lssl -lcrypto -fPIC -pthread -std=c++1y -DNDEBUG")
# Target system
set( SRCFILES
	./example.cpp
	./mylib.cpp
	)

add_executable(prueba ${SRCFILES} )
add_library(mylib ${SRCFILES} ) 
#TODO Add find_library for each  link
# target_link_libraries (test gtest gmock pthread )
# target_link_libraries (test)
