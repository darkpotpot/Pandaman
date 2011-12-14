
HEADERS += \
    simu.h \
    grid_display.h \
    grid.h \
    global.h \
    entity.h \
    drawing_helpers.h \
    displayer.h \
    displayable.h \
    controler.h \
    command.h \
    character_displayer.h \
    character.h \
    cell_displayer.h \
    cell.h \
    tinyxml/tinyxml.h \
    tinyxml/tinystr.h

SOURCES += \
    simu.cpp \
    main.cpp \
    grid_display.cpp \
    grid.cpp \
    global.cpp \
    entity.cpp \
    drawing_helpers.cpp \
    displayer.cpp \
    displayable.cpp \
    controler.cpp \
    character_displayer.cpp \
    character.cpp \
    cell_displayer.cpp \
    cell.cpp \
    tinyxml/tinyxmlparser.cpp \
    tinyxml/tinyxmlerror.cpp \
    tinyxml/tinyxml.cpp \
    tinyxml/tinystr.cpp

OTHER_FILES += \
    SConstruct

INCLUDEPATH += \
    /usr/include/python2.6 \
    /usr/include/panda3d

TARGET = main
