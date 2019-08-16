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
#include "crashhandler.h"
#include "rawlog.h"
#include "./Afps/Protocol/wmvolley.h"
#include "./Afps/Model/regfloatwritevm.h"
#include "./Afps/Model/regfloatreadvm.h"
#include "./Afps/Model/regmodulevm.h"
#include "./Afps/Model/monitormodule.h"
#include "./Afps/sampledata.h"
#include "./Afps/Model/adchartvm.h"
#include "./Afps/Model/singleaccuchartmodel.h"

int main(int argc, char *argv[])
{
    qDebug() << "main thread id " << QThread::currentThread();
    //注冊异常捕获函数
    SetUnhandledExceptionFilter((LPTOP_LEVEL_EXCEPTION_FILTER)ApplicationCrashHandler);

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
    qRegisterMetaType<AD_CHANNEDL_DATA>("AD_CHANNEDL_DATA");
    qRegisterMetaType<AxisRange>("AxisRange");
    RequestStyle::registType();
    ProtContent::regist();
    RegReadWriteModel::regist();
    ParaMonitor::regist();

    QQmlApplicationEngine engine;
    QQmlContext *context = engine.rootContext();

    //接口模块
    Interface *mInterface = new Interface();
    QQmlEngine::setObjectOwnership(mInterface, QQmlEngine::CppOwnership);
    //通讯历史数据
    RawLog* rawLog = new RawLog(1000);
    QObject::connect(mInterface->getSerialPortControl(), &SerialPortControl::sig_receive,
            rawLog, &RawLog::slot_receive);
    QObject::connect(mInterface->getSerialPortControl(), &SerialPortControl::sig_send,
            rawLog, &RawLog::slot_send);
    QQmlEngine::setObjectOwnership(rawLog, QQmlEngine::CppOwnership);
    //荧光协议
    WmVolley::instance()->getRequestQueue()->setSerial(mInterface->getSerialPortControl());
    WmVolley::instance()->getRequestQueue()->setRawLog(rawLog);
    QObject::connect(mInterface->getSerialPortControl(), &SerialPortControl::sig_receive,
                     WmVolley::instance()->getParseTh(), &ParseTh::slot_receiveData);
    /* AD 采集数据 */
    SampleData* sampleData = new SampleData();
    QObject::connect(WmVolley::instance()->getParseTh(), &ParseTh::sig_upload,
                     sampleData, &SampleData::slot_upload);
    QObject::connect(sampleData, &SampleData::sig_rcvData,
            mInterface->getAfpsAdChartModel(), &AdChartModel::slot_rcvData, Qt::QueuedConnection);
    QObject::connect(sampleData, &SampleData::sig_rcvData,
            mInterface->getAfpsDataStorage(), &AfpsDataStorage::on_addData);
    QObject::connect(sampleData, &SampleData::sig_rcvData,
            mInterface->getAlgorithm(), static_cast<void(Algorithm::*)(AD_CHANNEDL_DATA)>(&Algorithm::slot_receiveData));

    /* 荧光寄存器 */
    RegModuleVM* regModule = new RegModuleVM();
    /* 参数监测 */
    MonitorModule* monitor = new MonitorModule();
    QObject::connect(mInterface->getSerialPortControl(), &SerialPortControl::sig_state,
            monitor, &MonitorModule::slot_serialPortState);
    QQmlEngine::setObjectOwnership(monitor, QQmlEngine::CppOwnership);
    /* 谱图VM */
    AdChartVM* adChart1VM = new AdChartVM();
    QObject::connect(mInterface->getAfpsAdChartModel(), &AdChartModel::sig_ch1Data,
                     adChart1VM, &AdChartVM::slot_receiveData);
    AdChartVM* adChart2VM = new AdChartVM();
    QObject::connect(mInterface->getAfpsAdChartModel(), &AdChartModel::sig_ch2Data,
                     adChart2VM, &AdChartVM::slot_receiveData);
    AdChartVM* adChart3VM = new AdChartVM();
    QObject::connect(mInterface->getAfpsAdChartModel(), &AdChartModel::sig_ch3Data,
                     adChart3VM, &AdChartVM::slot_receiveData);
    AdChartVM* adChart4VM = new AdChartVM();
    QObject::connect(mInterface->getAfpsAdChartModel(), &AdChartModel::sig_ch4Data,
                     adChart4VM, &AdChartVM::slot_receiveData);
    /* 流量图 */
    SingleAccuChartModel* flowModel = new SingleAccuChartModel(100);
    AdChartVM* flowVM = new AdChartVM();
    QObject::connect(monitor->get(7), &ParaMonitor::sig_valueChanged,
                     flowModel, &SingleAccuChartModel::slot_receiveData);
    QObject::connect(flowModel, &SingleAccuChartModel::sig_data,
                     flowVM, &AdChartVM::slot_receiveData);

    context->setContextProperty("mInterface",mInterface);
    context->setContextProperty("AfpsAlgorithmViewModel", mInterface->mAfpsAlgorithmViewModel);
    context->setContextProperty("RawLog", rawLog);
    context->setContextProperty("RegModule", regModule);
    context->setContextProperty("Monitor", monitor);
    context->setContextProperty("AdChart1VM", adChart1VM);
    context->setContextProperty("AdChart2VM", adChart2VM);
    context->setContextProperty("AdChart3VM", adChart3VM);
    context->setContextProperty("AdChart4VM", adChart4VM);
    context->setContextProperty("FlowVM", flowVM);

    engine.load(QUrl(QStringLiteral("qrc:/src/qml/main.qml")));

    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
