cmake_minimum_required(VERSION 3.28)
project(GameFrameworkCore CXX)

set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Submodules:
add_subdirectory(external/sdl3)

# Angel script:
set(ANGEL_SOURCE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/external/angelscript/sdk/angelscript/source")
set(ANGEL_ADDON_PATH "${CMAKE_CURRENT_SOURCE_DIR}/external/angelscript/sdk/add_on")
add_library(angelscript STATIC 
  # Core
  "${ANGEL_SOURCE_PATH}/as_atomic.cpp"
  "${ANGEL_SOURCE_PATH}/as_builder.cpp"
  "${ANGEL_SOURCE_PATH}/as_bytecode.cpp"
  "${ANGEL_SOURCE_PATH}/as_callfunc.cpp"
  "${ANGEL_SOURCE_PATH}/as_callfunc_x64_gcc.cpp"
  "${ANGEL_SOURCE_PATH}/as_compiler.cpp"
  "${ANGEL_SOURCE_PATH}/as_configgroup.cpp"
  "${ANGEL_SOURCE_PATH}/as_context.cpp"
  "${ANGEL_SOURCE_PATH}/as_datatype.cpp"
  "${ANGEL_SOURCE_PATH}/as_gc.cpp"
  "${ANGEL_SOURCE_PATH}/as_generic.cpp"
  "${ANGEL_SOURCE_PATH}/as_globalproperty.cpp"
  "${ANGEL_SOURCE_PATH}/as_memory.cpp"
  "${ANGEL_SOURCE_PATH}/as_module.cpp"
  "${ANGEL_SOURCE_PATH}/as_objecttype.cpp"
  "${ANGEL_SOURCE_PATH}/as_outputbuffer.cpp"
  "${ANGEL_SOURCE_PATH}/as_parser.cpp"
  "${ANGEL_SOURCE_PATH}/as_restore.cpp"
  "${ANGEL_SOURCE_PATH}/as_scriptcode.cpp"
  "${ANGEL_SOURCE_PATH}/as_scriptengine.cpp"
  "${ANGEL_SOURCE_PATH}/as_scriptfunction.cpp"
  "${ANGEL_SOURCE_PATH}/as_scriptnode.cpp"
  "${ANGEL_SOURCE_PATH}/as_scriptobject.cpp"
  "${ANGEL_SOURCE_PATH}/as_string.cpp"
  "${ANGEL_SOURCE_PATH}/as_string_util.cpp"
  "${ANGEL_SOURCE_PATH}/as_thread.cpp"
  "${ANGEL_SOURCE_PATH}/as_tokenizer.cpp"
  "${ANGEL_SOURCE_PATH}/as_typeinfo.cpp"
  "${ANGEL_SOURCE_PATH}/as_variablescope.cpp"

  # Alternate as_callfunc 
  #"${ANGEL_SOURCE_PATH}/as_callfunc_arm64.cpp"
  #"${ANGEL_SOURCE_PATH}/as_callfunc_arm.cpp"
  #"${ANGEL_SOURCE_PATH}/as_callfunc_e2k.cpp"
  #"${ANGEL_SOURCE_PATH}/as_callfunc_mips.cpp"
  #"${ANGEL_SOURCE_PATH}/as_callfunc_ppc_64.cpp"
  #"${ANGEL_SOURCE_PATH}/as_callfunc_ppc.cpp"
  #"${ANGEL_SOURCE_PATH}/as_callfunc_riscv64.cpp"
  #"${ANGEL_SOURCE_PATH}/as_callfunc_sh4.cpp"
  #"${ANGEL_SOURCE_PATH}/as_callfunc_x64_mingw.cpp"
  #"${ANGEL_SOURCE_PATH}/as_callfunc_x64_msvc.cpp"
  #"${ANGEL_SOURCE_PATH}/as_callfunc_xenon.cpp"
  #"${ANGEL_SOURCE_PATH}/as_callfunc_x86.cpp"

  # Addons
  "${ANGEL_ADDON_PATH}/contextmgr/contextmgr.cpp"
  "${ANGEL_ADDON_PATH}/datetime/datetime.cpp"
  "${ANGEL_ADDON_PATH}/debugger/debugger.cpp"
  "${ANGEL_ADDON_PATH}/scriptany/scriptany.cpp"
  "${ANGEL_ADDON_PATH}/scriptarray/scriptarray.cpp"
  "${ANGEL_ADDON_PATH}/scriptbuilder/scriptbuilder.cpp"
  "${ANGEL_ADDON_PATH}/scriptdictionary/scriptdictionary.cpp"
  "${ANGEL_ADDON_PATH}/scriptfile/scriptfile.cpp"
  "${ANGEL_ADDON_PATH}/scriptfile/scriptfilesystem.cpp"
  "${ANGEL_ADDON_PATH}/scriptgrid/scriptgrid.cpp"
  "${ANGEL_ADDON_PATH}/scripthandle/scripthandle.cpp"
  "${ANGEL_ADDON_PATH}/scripthelper/scripthelper.cpp"
  "${ANGEL_ADDON_PATH}/scriptmath/scriptmath.cpp"
  "${ANGEL_ADDON_PATH}/scriptmath/scriptmathcomplex.cpp"
  "${ANGEL_ADDON_PATH}/scriptsocket/scriptsocket.cpp"
  "${ANGEL_ADDON_PATH}/scriptstdstring/scriptstdstring.cpp"
  "${ANGEL_ADDON_PATH}/scriptstdstring/scriptstdstring_utils.cpp"
  "${ANGEL_ADDON_PATH}/serializer/serializer.cpp"
  "${ANGEL_ADDON_PATH}/weakref/weakref.cpp"
)

target_include_directories(angelscript PUBLIC 
  "${CMAKE_CURRENT_SOURCE_DIR}/external/angelscript/sdk/angelscript/include"
  "${CMAKE_CURRENT_SOURCE_DIR}/external/angelscript/sdk/add_on/contextmgr"
  "${CMAKE_CURRENT_SOURCE_DIR}/external/angelscript/sdk/add_on/datetime"
  "${CMAKE_CURRENT_SOURCE_DIR}/external/angelscript/sdk/add_on/debugger"
  "${CMAKE_CURRENT_SOURCE_DIR}/external/angelscript/sdk/add_on/scriptany"
  "${CMAKE_CURRENT_SOURCE_DIR}/external/angelscript/sdk/add_on/scriptarray"
  "${CMAKE_CURRENT_SOURCE_DIR}/external/angelscript/sdk/add_on/scriptbuilder"
  "${CMAKE_CURRENT_SOURCE_DIR}/external/angelscript/sdk/add_on/scriptdictionary"
  "${CMAKE_CURRENT_SOURCE_DIR}/external/angelscript/sdk/add_on/scriptfile"
  "${CMAKE_CURRENT_SOURCE_DIR}/external/angelscript/sdk/add_on/scriptgrid"
  "${CMAKE_CURRENT_SOURCE_DIR}/external/angelscript/sdk/add_on/scripthandle"
  "${CMAKE_CURRENT_SOURCE_DIR}/external/angelscript/sdk/add_on/scripthelper"
  "${CMAKE_CURRENT_SOURCE_DIR}/external/angelscript/sdk/add_on/scriptmath"
  "${CMAKE_CURRENT_SOURCE_DIR}/external/angelscript/sdk/add_on/scriptsocket"
  "${CMAKE_CURRENT_SOURCE_DIR}/external/angelscript/sdk/add_on/scriptstdstring"
  "${CMAKE_CURRENT_SOURCE_DIR}/external/angelscript/sdk/add_on/serializer"
  "${CMAKE_CURRENT_SOURCE_DIR}/external/angelscript/sdk/add_on/weakref"
)

# Game Framework:
add_library(game-framework-core STATIC 
  src/easy-window/builder.cpp
  src/easy-window/instance.cpp

  src/filesystem/filesystem-linux.cpp
  src/filesystem/utils.cpp

  src/init/builder.cpp
  src/init/instance.cpp
  
  src/angelscript.cpp
  src/event-poll.cpp
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
