cmake_minimum_required(VERSION 3.28)
project(GameFrameworkCore CXX)


set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Submodules:
add_subdirectory(external/sdl3)

# Angel script:
add_library(angelscript STATIC 
  external/angelscript/sdk/angelscript/source/as_atomic.cpp
  external/angelscript/sdk/angelscript/source/as_builder.cpp
  external/angelscript/sdk/angelscript/source/as_bytecode.cpp
  external/angelscript/sdk/angelscript/source/as_callfunc_arm64.cpp
  external/angelscript/sdk/angelscript/source/as_callfunc_arm.cpp
  external/angelscript/sdk/angelscript/source/as_callfunc.cpp
  external/angelscript/sdk/angelscript/source/as_callfunc_e2k.cpp
  external/angelscript/sdk/angelscript/source/as_callfunc_mips.cpp
  external/angelscript/sdk/angelscript/source/as_callfunc_ppc_64.cpp
  external/angelscript/sdk/angelscript/source/as_callfunc_ppc.cpp
  external/angelscript/sdk/angelscript/source/as_callfunc_riscv64.cpp
  external/angelscript/sdk/angelscript/source/as_callfunc_sh4.cpp
  external/angelscript/sdk/angelscript/source/as_callfunc_x64_gcc.cpp
  external/angelscript/sdk/angelscript/source/as_callfunc_x64_mingw.cpp
  external/angelscript/sdk/angelscript/source/as_callfunc_x64_msvc.cpp
  external/angelscript/sdk/angelscript/source/as_callfunc_x86.cpp
  external/angelscript/sdk/angelscript/source/as_callfunc_xenon.cpp
  external/angelscript/sdk/angelscript/source/as_compiler.cpp
  external/angelscript/sdk/angelscript/source/as_configgroup.cpp
  external/angelscript/sdk/angelscript/source/as_context.cpp
  external/angelscript/sdk/angelscript/source/as_datatype.cpp
  external/angelscript/sdk/angelscript/source/as_gc.cpp
  external/angelscript/sdk/angelscript/source/as_generic.cpp
  external/angelscript/sdk/angelscript/source/as_globalproperty.cpp
  external/angelscript/sdk/angelscript/source/as_memory.cpp
  external/angelscript/sdk/angelscript/source/as_module.cpp
  external/angelscript/sdk/angelscript/source/as_objecttype.cpp
  external/angelscript/sdk/angelscript/source/as_outputbuffer.cpp
  external/angelscript/sdk/angelscript/source/as_parser.cpp
  external/angelscript/sdk/angelscript/source/as_restore.cpp
  external/angelscript/sdk/angelscript/source/as_scriptcode.cpp
  external/angelscript/sdk/angelscript/source/as_scriptengine.cpp
  external/angelscript/sdk/angelscript/source/as_scriptfunction.cpp
  external/angelscript/sdk/angelscript/source/as_scriptnode.cpp
  external/angelscript/sdk/angelscript/source/as_scriptobject.cpp
  external/angelscript/sdk/angelscript/source/as_string.cpp
  external/angelscript/sdk/angelscript/source/as_string_util.cpp
  external/angelscript/sdk/angelscript/source/as_thread.cpp
  external/angelscript/sdk/angelscript/source/as_tokenizer.cpp
  external/angelscript/sdk/angelscript/source/as_typeinfo.cpp
  external/angelscript/sdk/angelscript/source/as_variablescope.cpp
)

target_include_directories(angelscript PUBLIC 
  "${CMAKE_CURRENT_SOURCE_DIR}/external/angelscript/sdk/angelscript/include"
)

# Game Framework:
add_library(game-framework-core STATIC 
  src/easy-window/builder.cpp
  src/easy-window/instance.cpp

  src/init/builder.cpp
  src/init/instance.cpp

  src/event-poll.cpp
  src/filesystem.cpp
  src/logging.cpp
  src/utils.cpp
)

target_link_libraries(game-framework-core PUBLIC
  # Libraries:
  SDL3::SDL3
  angelscript
)
target_include_directories(game-framework-core PUBLIC 
  "${CMAKE_CURRENT_SOURCE_DIR}/include"
)

install(TARGETS game-framework-core RUNTIME DESTINATION bin)
