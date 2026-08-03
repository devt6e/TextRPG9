cmake_minimum_required(VERSION 3.20)
project(TextRPG9 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# src 폴더 아래 모든 .cpp 파일을 자동으로 수집
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS "src/*.cpp")
# include 폴더 아래 모든 .h 파일을 자동으로 수집
file(GLOB_RECURSE HEADERS CONFIGURE_DEPENDS "include/*.h")

add_executable(TextRPG9 ${SOURCES} ${HEADERS})

# include 폴더를 헤더 검색 경로로 추가
target_include_directories(TextRPG9 PRIVATE include)

if(MSVC)
    target_compile_options(TextRPG9 PRIVATE /utf-8)
endif()