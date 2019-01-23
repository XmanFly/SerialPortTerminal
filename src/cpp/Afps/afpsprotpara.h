#ifndef AFPSPROTPARA_H
#define AFPSPROTPARA_H

#include <QByteArray>
#include <QDebug>

//设备类型
enum DEV_ID {
    DEV_AD, //4通道AD数据
};
Q_DECLARE_METATYPE(DEV_ID)

enum PROT_FIELD {
    HEAD, //协议头
    LEN, //长度
    REGIST, //寄存器
    CONTENT, //内容
    CHECK_SUM, //校验码
};
Q_DECLARE_METATYPE(PROT_FIELD)


/* 协议各个字段 */
class AfpsProtPara
{
public:
    /* 协议头 */
    static const char CMD_HEAD = 0xAA;
    /* 寄存器 */
    static const char RGST_AD = 0x51;
    /* 各个字段长度 */
    static const char HEAD_LEN = 1;
    static const char LENGTH_LEN = 1;
    static const char REGIST_LEN = 1;
    static const char CHECKSUM_LEN = 1;
};

#endif // AFPSPROTPARA_H
