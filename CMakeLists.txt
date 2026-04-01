cmake_minimum_required(VERSION 3.28)
project(GameFrameworkWindow CXX)

set(EXECUTABLE_NAME game-framework-core)

set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Submodules:
add_subdirectory(external/sdl3)

add_executable(${EXECUTABLE_NAME} 
  src/window.cpp
)

target_link_libraries(${EXECUTABLE_NAME} PRIVATE
  # Libraries:
  sdl3
)
target_include_directories(${EXECUTABLE_NAME} PRIVATE 
  "${CMAKE_SOURCE_DIR}/include"
)

install(TARGETS ${EXECUTABLE_NAME} RUNTIME DESTINATION bin)
