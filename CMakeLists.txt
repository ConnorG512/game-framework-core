cmake_minimum_required(VERSION 3.28)
project(GameFrameworkCore CXX)

set(LIB_NAME game-framework-core)

set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Submodules:
add_subdirectory(external/sdl3)

add_library(${LIB_NAME} STATIC 
  src/init/builder.cpp
  src/init/instance.cpp
  src/event-poll.cpp
  src/utils.cpp
  src/window.cpp
)

target_link_libraries(${LIB_NAME} PRIVATE
  # Libraries:
  SDL3::SDL3
)
target_include_directories(${LIB_NAME} PUBLIC 
  "${CMAKE_CURRENT_SOURCE_DIR}/include"
)

install(TARGETS ${LIB_NAME} RUNTIME DESTINATION bin)
