QT += quick serialport charts
CONFIG += c++11

LIBS += -lDbgHelp

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
    src/cpp/Afps/Model/regfloatreadvm.cpp \
    src/cpp/Afps/Model/regfloatvm.cpp \
    src/cpp/Afps/Model/regfloatwritevm.cpp \
    src/cpp/Afps/Model/regreadwritemodel.cpp \
    src/cpp/Afps/Protocol/datarequest.cpp \
    src/cpp/Afps/Protocol/floatrequest.cpp \
    src/cpp/Afps/Protocol/parsefsm.cpp \
    src/cpp/Afps/Protocol/parseth.cpp \
    src/cpp/Afps/Protocol/protutils.cpp \
    src/cpp/Afps/Protocol/request.cpp \
    src/cpp/Afps/Protocol/requestqueue.cpp \
    src/cpp/Afps/Protocol/wmvolley.cpp \
    src/cpp/crashhandler.cpp \
    src/cpp/rawlog.cpp \
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
    src/cpp/rcvdatamodule.cpp \
    src/cpp/Afps/afpsparse.cpp \
    src/cpp/DummyData/dummydatabasic.cpp \
    src/cpp/DummyData/afpsdummydata.cpp \
    src/cpp/Afps/adchanneldev.cpp \
    src/cpp/Afps/afpsformat.cpp \
    src/cpp/Afps/afpsmodule.cpp \
    src/cpp/Afps/afpsdevmng.cpp \
    src/cpp/Afps/afpsdevbasic.cpp \
    src/cpp/Afps/afpsprotgen.cpp \
    src/cpp/Afps/afpsparsemodule.cpp \
    src/cpp/Afps/adchartmodel.cpp \
    src/cpp/Afps/afpslogic.cpp \
    src/cpp/Afps/afpsdatastorage.cpp \
    src/cpp/Afps/comboboxmodel.cpp \
    src/cpp/Afps/afpscfgparamodule.cpp \
    src/cpp/Afps/loaddatafile.cpp \
    src/cpp/Afps/Algorithm/algorithmviewmodel.cpp \
    src/cpp/Afps/Algorithm/alogorithm.cpp \
    src/cpp/Afps/Algorithm/baseline.cpp \
    src/cpp/Afps/Algorithm/detection.cpp \
    src/cpp/Afps/Algorithm/algorithmrespository.cpp

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
    src/cpp/Afps/Model/regfloatreadvm.h \
    src/cpp/Afps/Model/regfloatvm.h \
    src/cpp/Afps/Model/regfloatwritevm.h \
    src/cpp/Afps/Model/regreadwritemodel.h \
    src/cpp/Afps/Protocol/datarequest.h \
    src/cpp/Afps/Protocol/floatrequest.h \
    src/cpp/Afps/Protocol/parsefsm.h \
    src/cpp/Afps/Protocol/parseth.h \
    src/cpp/Afps/Protocol/protcontent.h \
    src/cpp/Afps/Protocol/protpara.h \
    src/cpp/Afps/Protocol/protutils.h \
    src/cpp/Afps/Protocol/request.h \
    src/cpp/Afps/Protocol/requestqueue.h \
    src/cpp/Afps/Protocol/wmvolley.h \
    src/cpp/crashhandler.h \
    src/cpp/rawlog.h \
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
    src/cpp/rcvdatamodule.h \
    src/cpp/ProtBasic/parsebasic.h \
    src/cpp/ProtBasic/protformatbasic.h \
    src/cpp/Afps/afpsparse.h \
    src/cpp/DummyData/dummydatabasic.h \
    src/cpp/DummyData/afpsdummydata.h \
    src/cpp/Afps/afpsdbgswitch.h \
    src/cpp/Afps/adchanneldev.h \
    src/cpp/Afps/afpsformat.h \
    src/cpp/Afps/afpsmodule.h \
    src/cpp/Afps/afpsdevmng.h \
    src/cpp/Afps/afpsdevbasic.h \
    src/cpp/ProtBasic/devbasic.h \
    src/cpp/ProtBasic/protgenbasic.h \
    src/cpp/Afps/afpsprotgen.h \
    src/cpp/Afps/afpsprotpara.h \
    src/cpp/Afps/afpsparsemodule.h \
    src/cpp/Afps/adchartmodel.h \
    src/cpp/Afps/afpslogic.h \
    src/cpp/Afps/afpsdatastorage.h \
    src/cpp/Afps/comboboxmodel.h \
    src/cpp/Afps/afpscfgparamodule.h \
    src/cpp/Afps/loaddatafile.h \
    src/cpp/Afps/Algorithm/algorithmviewmodel.h \
    src/cpp/Afps/Algorithm/algorithm.h \
    src/cpp/Afps/Algorithm/baseline.h \
    src/cpp/Afps/Algorithm/detection.h \
    src/cpp/Afps/Algorithm/leastsquare.h \
    src/cpp/Afps/Algorithm/algorithmrespository.h


win32-msvc* {
   QMAKE_CXXFLAGS += /MP
   QMAKE_CXXFLAGS_RELEASE += /Zi
}

#设置编码统一使用utf8
QMAKE_CXXFLAGS += -utf-8
#生成pdb文件
QMAKE_LFLAGS_RELEASE += /MAP
QMAKE_CFLAGS_RELEASE += /Zi
QMAKE_LFLAGS_RELEASE += /debug /opt:ref

QMAKE_LFLAGS_DEBUG += /MAP
QMAKE_CFLAGS_DEBUG += /Zi
QMAKE_LFLAGS_DEBUG += /debug /opt:ref

DESTDIR = $$PWD/bin
