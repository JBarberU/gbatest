cmake_minimum_required(VERSION 3.0)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_gba/Modules")

include(GBAEnv)
include(GBAMacros)

project(gbatest)
set(EXE_NAME ${PROJECT_NAME})

set(SRC
  src/test.c
)

add_executable(${EXE_NAME} ${SRC} ${HEADERS})
gba_target_props(${EXE_NAME})
objcopy_file(${EXE_NAME})
fix_gba(${EXE_NAME})
