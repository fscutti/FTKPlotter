#----------------------------------------------------------------
# Generated CMake target import file for configuration "RelWithDebInfo".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "UserAnalysis::FTKPlotsLib" for configuration "RelWithDebInfo"
set_property(TARGET UserAnalysis::FTKPlotsLib APPEND PROPERTY IMPORTED_CONFIGURATIONS RELWITHDEBINFO)
set_target_properties(UserAnalysis::FTKPlotsLib PROPERTIES
  IMPORTED_LOCATION_RELWITHDEBINFO "${_IMPORT_PREFIX}/lib/libFTKPlotsLib.so"
  IMPORTED_SONAME_RELWITHDEBINFO "libFTKPlotsLib.so"
  )

list(APPEND _IMPORT_CHECK_TARGETS UserAnalysis::FTKPlotsLib )
list(APPEND _IMPORT_CHECK_FILES_FOR_UserAnalysis::FTKPlotsLib "${_IMPORT_PREFIX}/lib/libFTKPlotsLib.so" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
