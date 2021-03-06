find_package(VTK COMPONENTS ${VTK_REQUIRED_COMPONENTS_BY_MODULE} REQUIRED)

if(MITK_USE_Qt5)
  find_package(Qt5Widgets REQUIRED QUIET)
endif()

list(APPEND ALL_INCLUDE_DIRECTORIES ${VTK_INCLUDE_DIRS})
list(APPEND ALL_LIBRARIES ${VTK_LIBRARIES})
