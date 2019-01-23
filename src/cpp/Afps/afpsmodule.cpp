#include "afpsmodule.h"

AfpsModule::AfpsModule(QObject *parent) : QObject(parent)
{
    qRegisterMetaType<AfpsFormat>("AfpsFormat");
    //解析模块
    mAfpsParseModule = new AfpsParseModule();
    AfpsParse *mParseIf =
            new AfpsParse();
    mAfpsParseModule->setParseIf(
                reinterpret_cast<ParseBasic<QByteArray,  AfpsFormat > *>(mParseIf));
    QThread *afpsTh = new QThread();
    mAfpsParseModule->moveToThread(afpsTh);
    afpsTh->start();

    //设备管理模块
    mAfpsDevMng = new AfpsDevMng();
    mAdChannelDev = new AdChannelDev(DEV_ID::DEV_AD);
    mAfpsDevMng->addDev(mAdChannelDev);
    mAfpsDevMng->addFinish();
    connect(mAfpsParseModule, &AfpsParseModule::sig_result,
            mAfpsDevMng, &AfpsDevMng::sig_rcvProt);
//    connect(mAfpsParseModule, &ParseModule::sig_result,
//            mAfpsDevMng, &AfpsDevMng::slot_rcvProt);
}
