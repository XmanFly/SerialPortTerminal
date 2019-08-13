#include "wmvolley.h"
#include <QtQml>

WmVolley* WmVolley::pInstance = nullptr;
QMutex WmVolley::mutex;

WmVolley* WmVolley::instance()
{
    QMutexLocker lock(&mutex);
    if(pInstance == nullptr){
        qmlRegisterUncreatableMetaObject(RequestNameSpace::staticMetaObject, "wm", 1, 0, "RequestNamespace", "Access to enums only");
        pInstance = new WmVolley();
    }
    return pInstance;
}

WmVolley::WmVolley()
{
    /* 解析线程 */
    parseTh = new ParseTh();
    parseFsm = new ParseFsm();
    parseTh->setParseIf(parseFsm);
    QThread* parseThread = new QThread();
    parseTh->moveToThread(parseThread);
    parseThread->start(QThread::HighestPriority);
    /* 请求队列 */
    requestQueue = new RequestQueue(parseTh);
}

RequestQueue* WmVolley::getRequestQueue()
{
    return requestQueue;
}
