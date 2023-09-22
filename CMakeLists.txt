cmake_minimum_required(VERSION 3.27)
project(loginRegister)
include_directories("${PROJECT_SOURCE_DIR}")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED On)
add_library(database database.cpp database.h)
add_executable(loginRegister main.cpp)
target_link_libraries(loginRegister database)


include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/80306a7b5ec8ddaabd26540f2827b903d69e7a02.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(mainTest mainTest.cpp)
target_link_libraries(mainTest GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(mainTest)