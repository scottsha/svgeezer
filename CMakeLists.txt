project(svgeez)

cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

#include_directories(cmake)
include(conan.cmake)
conan_cmake_run(CONANFILE conanfile.py
        BASIC_SETUP CMAKE_TARGETS
        BUILD missing
        KEEP_RPATHS
        OPTIONS ${REGRESSION_DATA})

add_subdirectory(app)
add_subdirectory(src)
