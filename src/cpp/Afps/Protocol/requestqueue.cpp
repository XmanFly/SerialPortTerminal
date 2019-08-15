#include "requestqueue.h"

RequestQueue::RequestQueue(ParseTh *parseTh, QObject *parent) :
    QObject(parent),
    parseTh(parseTh)
{
    requestQueue = new QList<Request* >;
    timeStampCreater = new QAtomicInt();
    mutex = new QMutex();
}

RequestQueue::RequestQueue(SerialPortControl* serial, ParseTh *parseTh, QObject *parent) :
    RequestQueue(parseTh, parent)
{
    this->serial = serial;
}

RequestQueue::~RequestQueue()
{
    delete requestQueue;
    delete timeStampCreater;
    delete mutex;
}

void RequestQueue::setSerial(SerialPortControl* serial)
{
    this->serial = serial;
}

Request *RequestQueue::addRequest(Request* req)
{
    QMutexLocker lock(mutex);
    req->setTimeStamp(
                static_cast<uchar>(timeStampCreater->fetchAndAddAcquire(1)%256));
    connect(req, &Request::sig_send,
            serial, &SerialPortControl::slot_send);
    connect(req, &Request::sig_send,
            rawLog, &RawLog::slot_send);
    connect(parseTh, &ParseTh::sig_response,
            req, &Request::slot_receiveResponse);
    connect(parseTh, &ParseTh::sig_err,
            req, &Request::slot_receiveErr);
    requestQueue->append(req);
    req->start();
    return req;
}

void RequestQueue::removeRequest(Request *req)
{
    QMutexLocker lock(mutex);
    requestQueue->removeOne(req);
    delete req;
    req = nullptr;
    qDebug() << "RequestQueue::removeRequest left size " << requestQueue->size();
}

void RequestQueue::setRawLog(RawLog *value)
{
    rawLog = value;
}
