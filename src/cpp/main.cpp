#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "interface.h"
#include "serialportpara.h"
#include "dataobject.h"
#include "datacntmodel.h"
#include "formatmodel.h"
#include "serialportparanonqobj.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    qmlRegisterType<Interface>("SerialPortTerminal.Interface", 1, 0, "Interface");
    qmlRegisterType<SerialPortPara>("SerialPortTerminal.SerialPortPara", 1, 0, "SerialPortPara");
    qmlRegisterType<DataObject>("SerialPortTerminal.DataObject", 1, 0, "DataObject");
    qmlRegisterType<TableModel>("SerialPortTerminal.TableModel", 1, 0, "TableModel");
    qmlRegisterType<DataCntModel>("SerialPortTerminal.DataCntModel", 1, 0, "DataCntModel");
    qmlRegisterType<FormatModel>("SerialPortTerminal.FormatModel", 1, 0, "FormatModel");
    qRegisterMetaType<SerialPortParaNonQobj>("SerialPortParaNonQobj");

//    QQmlContext *context = engine.rootContext();
//    Interface *mInterface = new Interface();
//    context->setContextProperty("Interface",mInterface);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/src/qml/main.qml")));



    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
