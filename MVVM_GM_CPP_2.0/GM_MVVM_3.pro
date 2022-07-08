QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    app/app.cpp \
    app/main.cpp \
    base/hook.cpp \
    base/level.cpp \
    base/map.cpp \
    base/mine.cpp \
    base/player.cpp \
    base/role.cpp \
    model/model.cpp \
    viewmodel/command/buyitemscommand.cpp \
    viewmodel/command/frameruncommand.cpp \
    viewmodel/command/gameresetcommand.cpp \
    viewmodel/command/playersetcommand.cpp \
    viewmodel/command/useboomcommand.cpp \
    viewmodel/viewmodel.cpp \
    windows/gameview.cpp \
    windows/sinks/mainwindowcommandsink.cpp

HEADERS += \
    app/app.h \
    base/hook.h \
    base/level.h \
    base/map.h \
    base/mine.h \
    base/player.h \
    base/role.h \
    common/etlbase.h \
    common/precomp.h \
    model/model.h \
    viewmodel/command/buyitemscommand.h \
    viewmodel/command/frameruncommand.h \
    viewmodel/command/gameresetcommand.h \
    viewmodel/command/playersetcommand.h \
    viewmodel/command/useboomcommand.h \
    viewmodel/viewmodel.h \
    windows/gameview.h \
    windows/sinks/mainwindowcommandsink.h

FORMS += \
#    view.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
