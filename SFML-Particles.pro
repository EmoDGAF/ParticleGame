TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        button.cpp \
        fire.cpp \
        main.cpp \
        oil.cpp \
        particle.cpp \
        sand.cpp \
        smoke.cpp \
        water.cpp \
        wood.cpp \
        world.cpp

QMAKE_CXXFLAGS += -O3 -finline-small-functions -momit-leaf-frame-pointer -pthread
@
QMAKE_CXXFLAGS_RELEASE -= -O2
QMAKE_CXXFLAGS_RELEASE += -O3

QMAKE_LFLAGS_RELEASE -= -O1
@

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../SFML-2.5.1/lib/ -lsfml-system-d
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../SFML-2.5.1/lib/ -lsfml-system-d

INCLUDEPATH += $$PWD/../SFML-2.5.1/include
DEPENDPATH += $$PWD/../SFML-2.5.1/include

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../SFML-2.5.1/lib/ -lsfml-graphics-d
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../SFML-2.5.1/lib/ -lsfml-graphics-d

INCLUDEPATH += $$PWD/../SFML-2.5.1/include
DEPENDPATH += $$PWD/../SFML-2.5.1/include

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../SFML-2.5.1/lib/ -lsfml-window-d
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../SFML-2.5.1/lib/ -lsfml-window-d

INCLUDEPATH += $$PWD/../SFML-2.5.1/include
DEPENDPATH += $$PWD/../SFML-2.5.1/include

HEADERS += \
    button.h \
    fire.h \
    oil.h \
    particle.h \
    sand.h \
    smoke.h \
    water.h \
    wood.h \
    world.h




