# -------------------------------------------------------------------------------
# applications
# -------------------------------------------------------------------------------
project(test_server)
cmake_minimum_required(VERSION 3.15)


file(GLOB_RECURSE SOURCES
"*.*"
)

# -------------------------------------------------------------------------------
# Include directories
# -------------------------------------------------------------------------------
include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}
  "${BURONG_INCLUDE_DIR}"
)
# -------------------------------------------------------------------------------
add_executable(${PROJECT_NAME}  ${SOURCES})
target_link_libraries(${PROJECT_NAME} burongnet)