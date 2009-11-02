PROJECT(gluoncreator)

find_package(KDE4 REQUIRED)
find_package(Gluon REQUIRED)

include_directories(${KDE4_INCLUDES} ${GLUON_INCLUDES})

include(KDE4Defaults)

add_definitions(${QT_DEFINITIONS} ${KDE4_DEFINITIONS})

#add_subdirectory(plugins)

set(gluoncreator_SRCS
    plugins/plugin.cpp
    plugins/pluginloader.cpp
    widgets/propertywidgetitem.cpp
    widgets/propertywidget.cpp
    main.cpp
    mainwindow.cpp
    #models/scenemodel.cpp
    models/qobjecttreemodel.cpp
)

kde4_add_executable(gluoncreator ${gluoncreator_SRCS})
target_link_libraries(gluoncreator ${GLUON_LIBRARY})

install(TARGETS gluoncreator DESTINATION ${BIN_INSTALL_DIR})
install(FILES ui/gluoncreatorui.rc DESTINATION ${DATA_INSTALL_DIR}/gluoncreator)