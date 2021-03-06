cmake_minimum_required(VERSION 2.6)

if(NOT GLUON_BUILD_ALL)
    find_package(GluonGraphics REQUIRED)
endif()

include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR} ${GLUON_GRAPHICS_INCLUDES})

set(beamrenderercomponent_SRCS
    beamrenderercomponent.cpp
)

qt4_automoc(${beamrenderercomponent_SRCS})
add_library(gluon_component_beamrenderer SHARED ${beamrenderercomponent_SRCS})

if(GLUON_BUILD_ALL)
    add_dependencies(gluon_component_beamrenderer GluonEngine GluonGraphics)
endif()

set_target_properties(gluon_component_beamrenderer PROPERTIES VERSION ${GLUON_VERSION_STRING} SOVERSION ${GLUON_VERSION_STRING} DEFINE_SYMBOL MAKE_GLUON_COMPONENT_BEAMRENDERER_LIB)
target_link_libraries(gluon_component_beamrenderer GluonEngine ${GLUON_GRAPHICS_LIBS})

install(
    TARGETS
    gluon_component_beamrenderer
    DESTINATION
    ${LIB_INSTALL_DIR}/gluon
)