cmake_minimum_required(VERSION 2.8)

file(GLOB SOURCES
    includes/*.hpp
    src/*.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})
