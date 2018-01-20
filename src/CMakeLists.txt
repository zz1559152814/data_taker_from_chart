cmake_minimum_required(VERSION 2.8)
# SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g -ggdb") 
# SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall") 
include_directories(${PROJECT_SOURCE_DIR/lib})

if(COMMAND cmake_policy)
	cmake_policy(SET CMP0003 NEW)
	endif(COMMAND cmake_policy) 

add_executable(main main.cpp ProcessClass.cpp)
find_package(OpenCV REQUIRED) 
if(OpenCV_FOUND)
	include_directories(${OpenCV_INCLUDE_DIRS})
	target_link_libraries(main ${OpenCV_LIBS})  
else(OpenCV_FOUND)	
	message(FATAL_ERROR ${CMAKE_ROOT})
endif(OpenCV_FOUND)

set(MAIN main.cpp)






