project(gluonexamples_input_keyboardloop)
cmake_minimum_required(VERSION 2.6)

find_package(GluonInput REQUIRED)

include_directories(${GLUON_INPUT_INCLUDES})
include_directories(${CMAKE_BINARY_DIR})

########### next target ###############

set(gluonexamples_input_keyboardloop_SRCS
    gameloop.cpp
    main.cpp
)

qt4_automoc(${gluonexamples_input_keyboardloop_SRCS})
add_executable(gluonexamples_input_keyboardloop ${gluonexamples_input_keyboardloop_SRCS})
target_link_libraries(gluonexamples_input_keyboardloop ${GLUON_INPUT_LIBS} ${QT_QTCORE_LIBRARY} ${QT_QTGUI_LIBRARY})
