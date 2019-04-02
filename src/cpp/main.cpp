#include <QApplication>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "interface.h"
#include "serialportpara.h"
#include "dataobject.h"
#include "datacntmodel.h"
#include "formatmodel.h"
#include "serialportparanonqobj.h"
#include "./Afps/afpscfgparamodule.h"
#include "./Afps/Algorithm/algorithmviewmodel.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QApplication app(argc, argv);

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QCoreApplication::setOrganizationName("WeiMu");
    QCoreApplication::setOrganizationDomain("weimu.com");
    QCoreApplication::setApplicationName("AFPS");

    //中文支持
    QTextCodec *codec = QTextCodec::codecForName("GB2312");
    QTextCodec::setCodecForLocale(codec);

    qmlRegisterType<Interface>("SerialPortTerminal.Interface", 1, 0, "Interface");
    qmlRegisterType<SerialPortPara>("SerialPortTerminal.SerialPortPara", 1, 0, "SerialPortPara");
    qmlRegisterType<DataObject>("SerialPortTerminal.DataObject", 1, 0, "DataObject");
    qmlRegisterType<TableModel>("SerialPortTerminal.TableModel", 1, 0, "TableModel");
    qmlRegisterType<DataCntModel>("SerialPortTerminal.DataCntModel", 1, 0, "DataCntModel");
    qmlRegisterType<FormatModel>("SerialPortTerminal.FormatModel", 1, 0, "FormatModel");
    qmlRegisterType<AfpsCfgParaModule>("SerialPortTerminal.AfpsCfgParaModule", 1, 0, "AfpsCfgParaModule");
    qRegisterMetaType<SerialPortParaNonQobj>("SerialPortParaNonQobj");
    qRegisterMetaType<QVector<QVector<QPointF>>>("QVector<QVector<QPointF>>");

//    QQmlContext *context = engine.rootContext();
//    Interface *mInterface = new Interface();
//    context->setContextProperty("Interface",mInterface);


    QQmlApplicationEngine engine;
    QQmlContext *context = engine.rootContext();
    Interface *mInterface = new Interface();
    context->setContextProperty("mInterface",mInterface);
    context->setContextProperty("AfpsAlgorithmViewModel", mInterface->mAfpsAlgorithmViewModel);

    engine.load(QUrl(QStringLiteral("qrc:/src/qml/main.qml")));





    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
