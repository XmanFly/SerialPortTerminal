#ifndef PROTPARA_H
#define PROTPARA_H

#include <QObject>

enum CMD_TYPE {
    MASTER_SET, //设置
    MASTER_POLL_REAL, //查询实时值
    MASTER_POLL_SET, //查询设置值
    MASTER_RESPONSE, //上位机响应
    HOST_RESPONSE, //下位机 响应
    HOST_UPLOAD, //下位机 自主上传
    HOST_ERR, //下位机 错误
};

enum ERR_TYPE {
    DEV_ADDR_ERR, //设备地址（50）错误
    FUNC_CODE_ERR, //功能码错误
    LEN_ERR, //数据长度错误
    CRC_ERR, //CRC错误
    RGST_ADD_ERR, //寄存器地址错误
    OUT_RANGE_ERR, //设置数据超范围
    DECODE_ERR, //解码异常
    UNKNOWN, //未知
};

class ProtPara
{
public:
    /* 设备地址 */
    static const uchar MASTER_HEAD = 0x50;
    static const uchar HOST_HEAD = 0x51;

    /* 命令类型 */
    static const uchar MASTER_SET = 0x01;
    static const uchar MASTER_POLL_REAL = 0x00;
    static const uchar MASTER_POLL_SET = 0x08;
    static const uchar MASTER_RESPONSE = 0x05;
    static const uchar HOST_UPLOAD = 0x40;
    static const uchar HOST_ERR = 0x04;
    static const uchar HOST_RESPONSE = 0x05;

    /* 各字段长度 */
    static const int HEAD_LEN = 1;
    static const int TIME_STAMP_LEN = 1;
    static const int LEN_LEN = 1;
    static const int CMD_TYPE_LEN = 1;
    static const int ADDR_LEN = 1;
    static const int CRC_LEN = 2;
    static const int FIX_LEN = HEAD_LEN + TIME_STAMP_LEN
            + LEN_LEN + CMD_TYPE_LEN + ADDR_LEN + CRC_LEN; //固定字段长度

};

#endif // PROTPARA_H
