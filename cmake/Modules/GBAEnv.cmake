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

macro(GBA_TARGET_PROPS EXE_NAME)
  set_target_properties(${EXE_NAME}
   PROPERTIES
   LINK_FLAGS -specs=gba.specs
   COMPILER_FLAGS "-mthumb -mthumb-interwork"
  )
endmacro()

