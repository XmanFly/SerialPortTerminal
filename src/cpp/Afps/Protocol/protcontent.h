#ifndef PROTCONTENT_H
#define PROTCONTENT_H

#include <QObject>
#include "protpara.h"

class ProtContent
{
public:
    ProtContent() {
        this->timeStamp = 0;
        this->cmdType = MASTER_POLL_SET;
        this->addr = 0xFF;
        this->value = QByteArray();
    }
    ProtContent(const ProtContent &src) {
        this->timeStamp = src.timeStamp;
        this->cmdType = src.cmdType;
        this->addr = src.addr;
        this->value = src.value;
    }

    uchar timeStamp; //时间戳
    CMD_TYPE cmdType; //命令类型
    uchar addr; //寄存器地址
    QByteArray value; //寄存器值
};

#endif // PROTCONTENT_H
