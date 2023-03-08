cmake_minimum_required(VERSION 3.22.1)

set(ARTIFACT math-tool)
project(${ARTIFACT})

# === External dependencies === #
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# === Build options === #
set(CMAKE_BUILD_TYPE "debug")
set(CMAKE_CXX_STANDARD "17")
set(CMAKE_CXX_COMPILER "clang++")
set(CXX_COMMON_FLAGS "-std=c++${CMAKE_CXX_STANDARD} -Wall -Werror")
set(CMAKE_EXPORT_COMPILE_COMMANDS "true")
if (CMAKE_BUILD_TYPE STREQUAL "debug")
    set(CMAKE_CXX_FLAGS "${CXX_COMMON_FLAGS} -O0 -g -fsanitize=address,undefined,leak")
elseif (CMAKE_BUILD_TYPE STREQUAL "release")
    set(CMAKE_CXX_FLAGS "${CXX_COMMON_FLAGS} -O3")
endif ()

# === idk === #
include_directories("src")

# === APP === #
file(GLOB_RECURSE SRC CONFIGURE_DEPENDS
    src/*.cpp
    src/*.h
    src/*/*.cpp
    src/*/*.h
    src/*/*/*.cpp
    src/*/*/*.h
    src/*/*/*/*.cpp
    src/*/*/*/*.h
)
add_executable(${ARTIFACT} ${SRC})

# === TEST === #
enable_testing()
file(GLOB_RECURSE TEST CONFIGURE_DEPENDS
    src/math/linal/*.h
    test/*.cpp
    test/*.h
)
add_executable(${ARTIFACT}-test ${TEST})
target_link_libraries(
    ${ARTIFACT}-test
    GTest::gtest_main
)
include(GoogleTest)
gtest_discover_tests(${ARTIFACT}-test)
