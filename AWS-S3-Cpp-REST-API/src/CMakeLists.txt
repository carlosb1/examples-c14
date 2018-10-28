# ----------------------------------------------
# Executable + define linking libraries

    set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)
    #set(CMAKE_CXX_FLAGS "-fPIC -std=c++0x ${CMAKE_CXX_FLAGS} -g -ftest-coverage -fprofile-arcs")
    set(CMAKE_CXX_FLAGS "-fPIC -std=c++0x ${CMAKE_CXX_FLAGS}")
    add_executable(s3 main.cpp S3.cpp Helper.cpp)
	add_dependencies(s3 ${DEPENDENCIES})
	target_link_libraries(s3 ${LIBRARIES} curl)

   add_library(s3_wrap STATIC S3.cpp Helper.cpp S3_wrap.cpp)
   add_dependencies(s3_wrap ${DEPENDENCIES})
   target_link_libraries(s3_wrap ${LIBRARIES} curl)

   add_library(s3_wrap2 SHARED S3.cpp Helper.cpp S3_wrap.cpp)
   add_dependencies(s3_wrap2 ${DEPENDENCIES})
   target_link_libraries(s3_wrap2 ${LIBRARIES} curl)
