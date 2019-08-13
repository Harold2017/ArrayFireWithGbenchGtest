cmake_minimum_required(VERSION 3.14)
project(arryfire_gbench_gtest)

set(CMAKE_CXX_STANDARD 11)

include_directories(src)

find_package(ArrayFire REQUIRED)

# Locate GTest
find_package(GTest REQUIRED)
if (GTEST_FOUND)
    message("GTest FOUND")
    include_directories(${GTEST_INCLUDE_DIRS})
endif()

# Google Benchmark
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
find_package(GoogleBenchmark REQUIRED)
if (benchmark_FOUND)
    message("GoogleBenchmark FOUND")
    set(BENCHMARK_ENABLE_TESTING OFF CACHE BOOL "Suppressing benchmark's tests" FORCE)
    include_directories(${benchmark_INCLUDE_DIRS})
endif()

# OpenMP
#find_package(OpenMP REQUIRED)
if(OPENMP_FOUND)
    message("OPENMP FOUND")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
endif()

# common
add_library(arryfire_gbench
        main.cpp)
add_library(arryfire_gtest
        main.cpp)

# GTest
target_link_libraries(arryfire_gbench ArrayFire::af)
target_link_libraries(arryfire_gtest ${GTEST_LIBRARIES} pthread)

# Google Benchmark
target_link_libraries(arryfire_gtest ArrayFire::af)
target_link_libraries(arryfire_gbench ${benchmark_LIBRARIES} pthread)

function(addBenchmark name)
    add_executable(${name} src/${name}.cpp)
    target_link_libraries(${name} arryfire_gbench)
endfunction()

function(addTest name)
    add_executable(${name} tests/${name}.cpp)
    target_link_libraries(${name} arryfire_gtest)
endfunction()

addBenchmark(gbench_test)

addTest(gtest_test)
