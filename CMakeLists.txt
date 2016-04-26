cmake_minimum_required (VERSION 2.8)
project (Tracker)
set(CMAKE_VERBOSE_MAKEFILE 1)

#Adding gmock library
# Include directories
#Add test includes
include_directories ("./gmock-1.7.0/include")
include_directories ("./gmock-1.7.0/gtest/include")
add_subdirectory("./gmock-1.7.0")


#Add flags
#Debug flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -std=c++1y -ggdb")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -std=c++1y -DNDEBUG")
# Target system
set( SRCFILES
	./google_code_jam_qual13.cpp
	#./test_btree.cpp
	#./test_thread3.cpp       	
	#./test_thread2.cpp       	
	#./test_thread1.cpp       	
	#test1.cpp
	#example_unittest.cpp
	#unit_tests.cpp
	)

add_executable(test ${SRCFILES} )
#TODO Add find_library for each  link
target_link_libraries (test gtest gmock pthread )
