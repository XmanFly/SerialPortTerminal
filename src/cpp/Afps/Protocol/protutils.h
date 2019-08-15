#ifndef PROTUTILS_H
#define PROTUTILS_H

#include <QObject>
#include "protcontent.h"
#include "crc16.h"

class ProtUtils
{
public:
    /* 解析 */
    static void parseLen(QByteArray &src, uchar& len);
    static void parseTimeStamp(QByteArray &src, uchar& timeStamp);
    static void parseCmdType(QByteArray &src, CMD_TYPE& cmdType, bool& ok);
    static void parseRgstAddr(QByteArray &src, uchar& rgstAddr);
    static void parseValue(QByteArray &src, int len, QByteArray& value);
    static void parseCrc(QByteArray &src, int start, int len, bool& ok);
    static void parseErr(QByteArray errCode, ERR_TYPE& err);
    /* 生成 */
    static void cmdTypeToRaw(CMD_TYPE type, QByteArray &raw);
    static void contentToRaw(const ProtContent& src, QByteArray& dst);
};

#endif // PROTUTILS_H
