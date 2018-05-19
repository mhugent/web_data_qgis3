
########################################################
# Files

SET (webdata_SRCS
     webdatafiltermodel.cpp
     webdatamodel.cpp
     webdataplugin.cpp
)

SET (webdata_MOC_HDRS
     webdatamodel.h
     webdataplugin.h
)

SET (webdata_RCCS  resources.qrc)

########################################################
# Build

#QT5_WRAP_UI (webdata_UIS_H  ${webdata_UIS})

QT5_WRAP_CPP (webdata_MOC_SRCS  ${webdata_MOC_HDRS})

QT5_ADD_RESOURCES(webdata_RCC_SRCS ${webdata_RCCS})

ADD_LIBRARY (webdataplugin MODULE ${webdata_SRCS} ${webdata_MOC_SRCS} ${webdata_RCC_SRCS})

INCLUDE_DIRECTORIES(
  ${CMAKE_SOURCE_DIR}/src/core
  ${CMAKE_SOURCE_DIR}/src/core/expression
  ${CMAKE_SOURCE_DIR}/src/core/geometry
  ${CMAKE_SOURCE_DIR}/src/core/layertree
  ${CMAKE_SOURCE_DIR}/src/core/metadata
  ${CMAKE_SOURCE_DIR}/src/core/raster
  ${CMAKE_SOURCE_DIR}/src/core/symbology
  ${CMAKE_SOURCE_DIR}/src/gui
  ${CMAKE_SOURCE_DIR}/src/gui/layertree
  ${CMAKE_SOURCE_DIR}/src/plugins

  ${CMAKE_BINARY_DIR}/src/core
  ${CMAKE_BINARY_DIR}/src/gui
  ${CMAKE_BINARY_DIR}/src/ui
)
INCLUDE_DIRECTORIES(SYSTEM
${GDAL_INCLUDE_DIR}
)

TARGET_LINK_LIBRARIES(webdataplugin
  qgis_core
  qgis_gui
)


########################################################
# Install

INSTALL(TARGETS webdataplugin
  RUNTIME DESTINATION ${QGIS_PLUGIN_DIR}
  LIBRARY DESTINATION ${QGIS_PLUGIN_DIR})

