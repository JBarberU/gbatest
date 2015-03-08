cmake_minimum_required(VERSION 3.0)
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_VERSION 1)
set(CMAKE_SYSTEM_PROCESSOR arm-none-eabi)

set(DEVKITARM "$ENV{DEVKITARM}")
if (NOT DEVKITARM)
  message(FATAL_ERROR "You have to set DEVKITARM in your enviranment")
endif()

set(DEVKITPRO "$ENV{DEVKITPRO}")
if (NOT DEVKITPRO)
  message(FATAL_ERROR "You have to set DEVKITPRO in your enviranment")
endif()

set(CMAKE_C_COMPILER "${DEVKITARM}/bin/arm-none-eabi-gcc")
set(CMAKE_CXX_COMPILER "${DEVKITARM}/bin/arm-none-eabi-g++")
set(CMAKE_FIND_ROOT_PATH "${DEVKITARM}")
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)

project(gbatest)
set(EXE_NAME ${PROJECT_NAME})

set(SRC
  src/test.c
)

add_executable(${EXE_NAME} ${SRC} ${HEADERS})

set_target_properties(${EXE_NAME}
 PROPERTIES
 LINK_FLAGS -specs=gba.specs
 COMPILER_FLAGS "-mthumb -mthumb-interwork"
)

macro(OBJCOPY_FILE EXE_NAME)
  set(FI "${CMAKE_CURRENT_BINARY_DIR}/${EXE_NAME}")
  set(FO "${CMAKE_CURRENT_BINARY_DIR}/${EXE_NAME}.gba")
  message(STATUS ${FO})
  add_custom_command(
    OUTPUT "${FO}"
    COMMAND ${CMAKE_OBJCOPY}
    ARGS -O binary --verbose ${FI} ${FO}
    DEPENDS "${FI}"
  )
  add_custom_target("TargetObjCopy_${EXE_NAME}"
    ALL DEPENDS ${FO} VERBATIM)
  get_directory_property(extra_clean_files 
    ADDITIONAL_MAKE_CLEAN_FILES)
  set_directory_properties(
    PROPERTIES
    ADDITIONAL_MAKE_CLEAN_FILES "${extra_clean_files};${FO}")
  set_source_files_properties("${FO}" PROPERTIES GENERATED TRUE)
endmacro()

macro(FIX_GBA EXE_NAME)
  set(FI "${CMAKE_CURRENT_BINARY_DIR}/${EXE_NAME}.gba")
  add_custom_target("GBAFix_${EXE_NAME}"
    ALL DEPENDS "TargetObjCopy_${EXE_NAME}")
  add_custom_command(
    TARGET "GBAFix_${EXE_NAME}"
    COMMAND "${DEVKITARM}/bin/gbafix"
    ARGS "${FI}"
    DEPENDS "${FI}"
  )
endmacro()

objcopy_file(${EXE_NAME})
fix_gba(${EXE_NAME})
