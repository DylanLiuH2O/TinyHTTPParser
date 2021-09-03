cmake_minimum_required(VERSION 3.10)

project(TestHttpRequest)

SET(CMAKE_CXX_FLAGS_DEBUG "-O0 -g" )
SET(CMAKE_CXX_FLAGS_RELEASE "-O3 -g")

set(SOURCES
    ../src/HttpRequestParser.cc
    ../src/HttpRequest.cc
    TestHttpRequest.cc
)

add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME}
    PRIVATE
        ${PROJECT_SOURCE_DIR}/../include/
)