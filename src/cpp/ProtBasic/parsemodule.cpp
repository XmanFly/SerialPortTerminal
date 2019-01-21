#include "parsemodule.h"

ParseModule::ParseModule(QObject *parent) : QObject(parent)
{
    msgCnt = 0;
}

void ParseModule::setParseIf(ParseBasic<QByteArray,  AfpsFormat> *mParseIf)
{
    this->mParseIf = mParseIf;
}

void ParseModule::slot_receiveData(QByteArray data)
{
    //添加数据
    buffer.append(data);
    //进行解析
    AfpsFormat mProtResult;
    do {
        mParseIf->parse(buffer, mProtResult);
        if(mProtResult.getIsValid()) {
            emit sig_result(mProtResult);
            msgCnt++;
            qDebug() << "ParseModule::slot_receiveData "
                     << "message cnt " << msgCnt;
        }
    }while(mProtResult.getIsValid());
    qDebug() << "ParseModule::slot_receiveData "
             << "buffer size " << buffer.size();
}
