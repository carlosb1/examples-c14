cmake_minimum_required (VERSION 2.8)
project (Tracker)
set(CMAKE_VERBOSE_MAKEFILE 1)



include_directories ("../")
include_directories ("./")
include_directories ("./include")
include_directories ("../threads_examples")

#Add flags
#Debug flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -std=c++1y -DNDEBUG -DCMAKE_BUILD_TYPE=Release -DBENCHMARK_ENABLE_LTO=true")
# Target system
set( SRCFILES
	#	./reader_writer_problem.cpp
		./active_object_problem.cpp
	)
set( SRCFILES2
		monitor_template.cpp
	)

add_executable(test ${SRCFILES} )
add_executable(test2 ${SRCFILES2} )
#TODO Add find_library for each  link
#target_link_libraries (test  pthread )
target_link_libraries (test benchmark pthread )
target_link_libraries (test2 benchmark pthread )
