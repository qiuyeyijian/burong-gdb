# -------------------------------------------------------------------------------
# applications
# -------------------------------------------------------------------------------
project(buronggdb)
cmake_minimum_required(VERSION 3.15)

# -------------------------------------------------------------------------------
# CMake flags
# -------------------------------------------------------------------------------
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(EXECUTABLE_OUTPUT_PATH "${CMAKE_SOURCE_DIR}/build/bin")
set(LIBRARY_OUTPUT_PATH "${CMAKE_SOURCE_DIR}/build/lib")
set(BURONG_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(BURONG_INCLUDE_DIR ${BURONG_SOURCE_DIR}/include)
set(BURONG_INCLUDE_DIR ${BURONG_INCLUDE_DIR} ${BURONG_SOURCE_DIR}/lib/burongnet/include)

# set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-O2 -std=c++11 -rdynamic -lpthread -fPIC -lstdc++ -pipe -lrt -lpthread")


file(GLOB_RECURSE SOURCES
  "include/*.h"
  "include/*.hpp"
  "src/*.*"
)

# -------------------------------------------------------------------------------
# Include directories
# -------------------------------------------------------------------------------
include_directories(
  "${BURONG_INCLUDE_DIR}"
)
# -------------------------------------------------------------------------------
add_library(${PROJECT_NAME} STATIC ${SOURCES}) # 生成静态库

if(UNIX)
  message(" Current platform: Linux ")
  target_link_libraries(${PROJECT_NAME} rt pthread)
endif()

add_subdirectory(lib/burongnet)
add_subdirectory(test)