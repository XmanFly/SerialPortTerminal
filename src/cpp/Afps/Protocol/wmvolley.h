#ifndef WMVOLLEY_H
#define WMVOLLEY_H

#include <QObject>
#include <QMutex>
#include <QThread>
#include "requestqueue.h"
#include "parseth.h"
#include "parsefsm.h"

class WmVolley
{
public:
    static WmVolley* instance();
    ~WmVolley();
    RequestQueue* getRequestQueue();

private:
    WmVolley();
    RequestQueue* requestQueue; //消息请求队列
    ParseTh* parseTh; //解析线程
    ParseFsm* parseFsm; //解析状态机
    static WmVolley* pInstance;
    static QMutex mutex;
};

#endif // WMVOLLEY_H
