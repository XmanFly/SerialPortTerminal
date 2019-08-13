#include "protutils.h"
#include "protpara.h"

void ProtUtils::parseLen(QByteArray &src, uchar& len)
{
    len = static_cast<uchar>(src.at(0) & 0x00FF);
    src.remove(0, ProtPara::LEN_LEN);
}

void ProtUtils::parseTimeStamp(QByteArray &src, uchar &timeStamp)
{
    timeStamp = static_cast<uchar>(src.at(0) & 0x00FF);
    src.remove(0, ProtPara::TIME_STAMP_LEN);
}

void ProtUtils::parseCmdType(QByteArray &src, CMD_TYPE& cmdType, bool &ok)
{
    ok = true;
    switch (src.at(0)) {
    case ProtPara::HOST_UPLOAD:
        cmdType = CMD_TYPE::HOST_UPLOAD;
        break;
    case ProtPara::HOST_RESPONSE:
        cmdType = CMD_TYPE::HOST_RESPONSE;
        break;
    case ProtPara::HOST_ERR:
        cmdType = CMD_TYPE::HOST_ERR;
        break;
    default:
        ok = false;
    }
    src.remove(0, ProtPara::CMD_TYPE_LEN);
}

void ProtUtils::parseRgstAddr(QByteArray &src, uchar& rgstAddr)
{
    rgstAddr = static_cast<uchar>(src.at(0) & 0x00FF);
    src.remove(0, ProtPara::ADDR_LEN);
}

void ProtUtils::parseValue(QByteArray &src, int len, QByteArray& value)
{
    value = src.mid(0, len);
    src.remove(0, len);
}

void ProtUtils::cmdTypeToRaw(CMD_TYPE type, QByteArray& raw)
{
    raw.clear();
    switch (type) {
    case MASTER_SET:
        raw.append(static_cast<char>(ProtPara::MASTER_SET));
        break;
    case MASTER_POLL_REAL:
        raw.append(static_cast<char>(ProtPara::MASTER_POLL_REAL));
        break;
    case MASTER_POLL_SET:
        raw.append(static_cast<char>(ProtPara::MASTER_POLL_SET));
        break;
    }
}

void ProtUtils::contentToRaw(const ProtContent& src, QByteArray& dst)
{
    dst.clear();
    dst.append(ProtPara::MASTER_HEAD); //协议头
    dst.append(static_cast<char>(src.timeStamp)); //时间戳
    dst.append(static_cast<char>(ProtPara::CMD_TYPE_LEN+ProtPara::ADDR_LEN+src.value.size())); //长度
    QByteArray type;
    cmdTypeToRaw(src.cmdType, type);
    dst.append(type); //命令类型
    dst.append(static_cast<char>(src.addr)); //寄存器地址
    dst.append(src.value); //寄存器值
    //TBD CRC
    dst.append(0x11);
    dst.append(0x22);
}
