cmake_minimum_required(VERSION 3.0)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_gba/Modules")

include(GBAEnv)
find_package(LibGBA)

include(GBAMacros)

project(gbatest)
set(EXE_NAME ${PROJECT_NAME})

set(SRC
  src/test.cpp
)

add_executable(${EXE_NAME} ${SRC} ${HEADERS})
target_link_libraries(${EXE_NAME} PRIVATE ${LIBGBA_LIBRARIES})
include_directories(${EXE_NAME} ${LIBGBA_INCLUDE_DIRS})
gba_target_props(${EXE_NAME})
objcopy_file(${EXE_NAME})
fix_gba(${EXE_NAME})
