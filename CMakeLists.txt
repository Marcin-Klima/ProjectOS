cmake_minimum_required(VERSION 3.11)
project(ProjectOS CXX)

set(CMAKE_CXX_STANDARD 17)

message(STATUS "The host processor is ${CMAKE_HOST_SYSTEM_PROCESSOR}")

if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
	message(STATUS "Compiling using Clang (LLVM) compiler")
	set(CMAKE_CXX_FLAGS "-Wall -Werror -std=c++17")
	set(CMAKE_CXX_FLAGS_RELEASE "-O2")
	set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g")
endif()

message(STATUS "Compiling for ${CMAKE_SYSTEM_NAME} system")

if(${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
	add_definitions(-DSYSTEM_LINUX)
endif()

add_subdirectory(tests)
add_subdirectory(src)
include_directories(src)

file(GLOB SOURCES src)
add_executable(ProjectOS ${SOURCES})

find_package(Curses REQUIRED)
find_package(Threads REQUIRED)

target_link_libraries(ProjectOS src)
target_link_libraries(ProjectOS ${CURSES_LIBRARIES})
target_link_libraries(ProjectOS ${CMAKE_THREAD_LIBS_INIT})