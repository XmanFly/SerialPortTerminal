#ifndef PROTPARA_H
#define PROTPARA_H

#include <QByteArray>
#include <QDebug>

//设备类型
enum DEV {
    DEV_AD, //4通道AD数据
};
Q_DECLARE_METATYPE(DEV)

enum PROT_FIELD {
    HEAD, //协议头
    LEN, //长度
    REGIST, //寄存器
    CONTENT, //内容
    CHECK_SUM, //校验码
};
Q_DECLARE_METATYPE(PROT_FIELD)



/* 协议各个字段 */
class ProtPara
{
public:
    /* 协议头 */
    static const uchar CMD_HEAD = 0xAA;
    /* 寄存器 */
    static const uchar RGST_AD = 0x51;

};

#endif // PROTPARA_H
