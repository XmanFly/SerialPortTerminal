QT += quick serialport
CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        ./src/cpp/main.cpp \
    src/cpp/serialportcontrol.cpp \
    src/cpp/interface.cpp \
    src/cpp/serialportpara.cpp \
    src/cpp/serialportparanonqobj.cpp \
    src/cpp/dataobject.cpp \
    src/cpp/serialdatamodel.cpp \
    src/cpp/tablemodel.cpp \
    src/cpp/periodsend.cpp \
    src/cpp/datacntmodule.cpp \
    src/cpp/datacntmodel.cpp \
    src/cpp/formatmodel.cpp \
    src/cpp/formatmodule.cpp \
    src/cpp/rcvdatamodule.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    src/cpp/serialportcontrol.h \
    src/cpp/interface.h \
    src/cpp/serialportpara.h \
    src/cpp/serialportparanonqobj.h \
    src/cpp/dataobject.h \
    src/cpp/serialdatamodel.h \
    src/cpp/tablemodel.h \
    src/cpp/periodsend.h \
    src/cpp/datacntmodule.h \
    src/cpp/datacntmodel.h \
    src/cpp/formatmodel.h \
    src/cpp/formatmodule.h \
    src/cpp/rcvdatamodule.h
