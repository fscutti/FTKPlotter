# The name of the package:
atlas_subdir (FTKPlots)

# Component(s) in the package:
atlas_add_root_dictionary (FTKPlotsLib
   FTKPlotsDictSource
   ROOT_HEADERS FTKPlots/*.h Root/LinkDef.h
   EXTERNAL_PACKAGES ROOT )

atlas_depends_on_subdirs( PUBLIC
                          Control/xAODRootAccess
                          Event/xAOD/xAODEventInfo
                          Event/xAOD/xAODTracking
                          Event/xAOD/xAODCore
                          Event/xAOD/xAODTruth
)

# add the library itself:
atlas_add_library (FTKPlotsLib
   FTKPlots/*.h FTKPlots/*.ihh Root/*.cxx ${FTKPlotsDictSource}
   PUBLIC_HEADERS FTKPlots
   INCLUDE_DIRS
   LINK_LIBRARIES EventLoop xAODEventInfo xAODRootAccess xAODTracking xAODTruth xAODCore
   PRIVATE_LINK_LIBRARIES 
   )


