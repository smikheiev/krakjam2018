QT += quick
CONFIG += c++11

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
    sources/main.cpp \
    sources/spinacz.cpp \
    sources/features/featuresroot.cpp \
    sources/features/appState/appstatefeature.cpp \
    sources/qmltypesregistrator.cpp \
    sources/features/exitApp/exitappfeature.cpp \
    sources/features/gameplay/gameplayfeature.cpp \
    sources/features/gameplay/map/mapmodel.cpp \
    sources/features/gameplay/map/tilemodel.cpp \
    sources/features/gameplay/range/rangemodel.cpp \
    sources/features/gameplay/range/rangeslistmodel.cpp

RESOURCES += \
    resources/qml.qrc \
    resources/images.qrc

HEADERS += \
    sources/spinacz.h \
    sources/features/featuresroot.h \
    sources/macros.h \
    sources/features/appState/appstatefeature.h \
    sources/features/appState/appstate.h \
    sources/qmltypesregistrator.h \
    sources/features/exitApp/exitappfeature.h \
    sources/features/gameplay/gameplayfeature.h \
    sources/features/gameplay/gameplaystate.h \
    sources/features/gameplay/map/mapmodel.h \
    sources/features/gameplay/map/tiletype.h \
    sources/features/gameplay/map/tilemodel.h \
    sources/features/gameplay/range/rangemodel.h \
    sources/features/gameplay/range/rangeslistmodel.h
