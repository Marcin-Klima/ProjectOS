include_directories(${PROJECT_SOURCE_DIR}/lib/googletest-master/googletest/include)
include_directories(${PROJECT_SOURCE_DIR}/lib/googletest-master/googletest)
include_directories(${PROJECT_SOURCE_DIR}/src)

add_executable(unit_tests unitTestsBasics.cpp)

target_link_libraries(unit_tests gtest gtest_main)
target_link_libraries(unit_tests src)