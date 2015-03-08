# Defines macro objcopy_file, which takes an EXE_NAME and creates ${EXE_NAME}.gba 
# Defines macro fix_gba, which takes an EXE_NAME, assumes objcopy has already ran and fixes the gba executable

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

