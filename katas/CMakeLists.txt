cmake_minimum_required (VERSION 2.8)
project (Tracker)
set(CMAKE_VERBOSE_MAKEFILE 1)



include_directories ("./")
include_directories ("./include")

link_directories("/home/carlos/c-workspace/examples-c14/katas/lib")


#Add flags
#Debug flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -std=c++1y -DNDEBUG -DCMAKE_BUILD_TYPE=Release -DBENCHMARK_ENABLE_LTO=true ")
# Target system
set( SRCFILES
		./test_dungeon.cpp
)

add_executable(test_dungeon ${SRCFILES} )

target_link_libraries (test_dungeon benchmark pthread CppReact)
