cmake_minimum_required(VERSION 3.10)

project(SUBD)

set(CMAKE_CXX_STANDARD 20)

file(GLOB
        CPPS "*.cpp")
add_executable(${PROJECT_NAME} ${CPPS})