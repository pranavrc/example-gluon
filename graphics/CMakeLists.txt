cmake_minimum_required(VERSION 2.6)

if(NOT GLUON_BUILD_ALL)
project(GluonGraphics)
    find_package(GluonCore REQUIRED)
endif()

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

if(WIN32)
    find_package(GLEE)
    if(NOT GLEE_FOUND)
        message(FATAL_ERROR "Could NOT find GLee!")
    endif(NOT GLEE_FOUND)
endif(WIN32)

add_definitions(-DGL_GLEXT_PROTOTYPES)

include_directories(
    ${CMAKE_CURRENT_BINARY_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${GLUON_CORE_INCLUDES}
    ${OPENGL_REAL_INCLUDE_DIR}
)

set(GLUON_GRAPHICS_INCLUDES
    ${GLUON_CORE_INCLUDES}
    ${OPENGL_REAL_INCLUDE_DIR}
    CACHE INTERNAL "Includes required for Gluon Graphics"
)

set(GluonGraphics_SRCS
    rendertarget.cpp
    backendcapabilities.cpp
    mathutils.cpp
    frustrum.cpp
    material.cpp
    materialinstance.cpp
    technique.cpp
    materialelement.cpp
    camera.cpp
    renderwidget.cpp
    viewport.cpp
    vertex.cpp
    texture.cpp
    item.cpp
    engine.cpp
    mesh.cpp
    vertexattribute.cpp
    vertexbuffer.cpp
)

set(GluonGraphics_HEADERS
    backendcapabilities.h
    gluon_graphics_export.h
    camera.h
    renderwidget.h
    viewport.h
    vertex.h
    texture.h
    item.h
    engine.h
    mesh.h
    mathutils.h
    frustrum.h
    material.h
    materialinstance.h
    technique.h
    materialelement.h
    vertexbuffer.h
    vertexattribute.h
    rendertarget.h
    glheaders.h
)

qt4_automoc(${GluonGraphics_SRCS})
add_library(GluonGraphics SHARED ${GluonGraphics_SRCS} ${GluonGraphics_HEADERS})

set_target_properties(GluonGraphics PROPERTIES VERSION ${GLUON_VERSION_STRING} SOVERSION ${GLUON_VERSION_STRING} DEFINE_SYMBOL MAKE_GLUON_GRAPHICS_LIB)

if(APPLE)
    #hack for being able to set headers as public in a osx framework
    list(APPEND GluonGraphics_HEADERS
            ${GluonGraphics_HEADERS}
    )

    set_target_properties(GluonGraphics PROPERTIES FRAMEWORK TRUE)
    set_target_properties(GluonGraphics PROPERTIES BUILD_WITH_INSTALL_RPATH 1 INSTALL_NAME_DIR "@executable_path/../Frameworks")
    set_target_properties(GluonGraphics PROPERTIES PUBLIC_HEADER "${GluonGraphics_HEADERS}")

    set(MACOSX_FRAMEWORK_IDENTIFIER graphics)
    set(MACOSX_FRAMEWORK_SHORT_VERSION_STRING ${GLUON_VERSION_STRING})
    set(MACOSX_FRAMEWORK_BUNDLE_VERSION ${GLUON_VERSION_STRING})
endif()

target_link_libraries(
    GluonGraphics
    ${GLUON_CORE_LIBS}
    ${QT_QTOPENGL_LIBRARY}
    ${OPENGL_REAL_LIBS}
)

set(GLUON_GRAPHICS_LIBS
    GluonGraphics
    ${GLUON_CORE_LIBS}
    ${QT_QTOPENGL_LIBRARY}
    ${OPENGL_REAL_LIBS}
    CACHE INTERNAL "Libraries required for Gluon Graphics"
)

if(WIN32)
    target_link_libraries(GluonGraphics ${GLEE_LIBRARIES})
    set(GLUON_GRAPHICS_LIBS
        ${GLUON_GRAPHICS_LIBS}
        ${GLEE_LIBRARIES}
        CACHE INTERNAL "Libararies required for Gluon Graphics"
    )
endif(WIN32)

if(INSTALL_EXAMPLES)
    add_subdirectory(examples)
endif()

install(
    TARGETS GluonGraphics
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION ${LIB_INSTALL_DIR}
    ARCHIVE DESTINATION ${LIB_INSTALL_DIR}
    FRAMEWORK DESTINATION ${LIB_INSTALL_DIR}
)

install(FILES
    ${GluonGraphics_HEADERS}
    DESTINATION ${INCLUDE_INSTALL_DIR}/gluon/graphics
    COMPONENT Devel
)

install(
    FILES
    default.png
    default.gml
    DESTINATION ${SHARE_INSTALL_DIR}/gluon/defaults
)
