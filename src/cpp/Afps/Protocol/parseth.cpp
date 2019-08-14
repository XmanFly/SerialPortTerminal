#include "parseth.h"
#include <QDebug>

ParseTh::ParseTh(QObject *parent) : QObject(parent)
{
    msgCnt = 0;
}

void ParseTh::setParseIf(ParseFsm *mParseIf)
{
    this->mParseIf = mParseIf;
}

void ParseTh::slot_receiveData(QByteArray data)
{
    qDebug() << TAG << "slot_receiveData "
             << "buffer size " << buffer.size()
             << "receive size " << data.size()
             << data.toHex();
    if(buffer.size() > 1024000){
        buffer.clear();
    }
    //添加数据
    buffer.append(data);
    //进行解析
    bool isOk;
    do {
        isOk = mParseIf->parse(buffer);
        if(isOk){
            switch (mParseIf->getResult().cmdType) {
            case HOST_RESPONSE:
                emit sig_response(mParseIf->getResult());
                break;
            case HOST_UPLOAD:
                emit sig_upload(mParseIf->getResult());
                break;
            case HOST_ERR:
                emit sig_err(mParseIf->getResult());
                break;
            }
            msgCnt++;
            qDebug() << TAG << "slot_receiveData "
                     << "message cnt " << msgCnt;
        }
    } while(isOk);
    qDebug() << TAG << "slot_receiveData "
             << "buffer size parse left " << buffer.size();
}
