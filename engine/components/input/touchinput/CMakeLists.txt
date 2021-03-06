cmake_minimum_required(VERSION 2.6)

if(NOT GLUON_BUILD_ALL)
    find_package(GluonInput REQUIRED)
endif()

include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR} ${GLUON_INPUT_INCLUDES})

set(touchinputcomponent_SRCS
    touchinputcomponent.cpp
)

qt4_automoc(${touchinputcomponent_SRCS})
add_library(gluon_component_touchinput SHARED ${touchinputcomponent_SRCS})

if(GLUON_BUILD_ALL)
    add_dependencies(gluon_component_touchinput GluonEngine GluonInput)
endif()

set_target_properties(gluon_component_touchinput PROPERTIES VERSION ${GLUON_VERSION_STRING} SOVERSION ${GLUON_VERSION_STRING} DEFINE_SYMBOL MAKE_GLUON_COMPONENT_TOUCHINPUT_LIB)
target_link_libraries(gluon_component_touchinput GluonEngine ${GLUON_INPUT_LIBS})

install(
    TARGETS
    gluon_component_touchinput
    DESTINATION
    ${LIB_INSTALL_DIR}/gluon
)
