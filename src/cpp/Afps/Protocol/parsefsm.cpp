#include "parsefsm.h"
#include <QDebug>

ParseFsm::ParseFsm()
{

}

ParseFsm::~ParseFsm()
{

}

bool ParseFsm::parse(QByteArray &buf)
{
    //协议头
    QByteArray head;
    head.append(ProtPara::HOST_HEAD);
    //查找协议头
    int headIdx = buf.indexOf(head);
    if(headIdx == -1){
        return false;
    }
    //解析长度字段
    if((headIdx+ProtPara::HEAD_LEN+ProtPara::TIME_STAMP_LEN+ProtPara::LEN_LEN)
            > buf.size()){
        qDebug() << TAG << "parse not have len field ";
        return false;
    }
    uchar lenField;
    int totalLen; //从buffer初始位置开始 到本条协议结尾
    int protLen; //本条协议长度
    lenField = static_cast<uchar>(buf.at(headIdx+ProtPara::HEAD_LEN+ProtPara::TIME_STAMP_LEN) & 0x00FF);
    protLen = ProtPara::HEAD_LEN+ProtPara::TIME_STAMP_LEN+ProtPara::LEN_LEN+lenField+ProtPara::CRC_LEN;
    totalLen = headIdx + protLen;
    //判断总长度是否达到
    if( totalLen > buf.size()){
        qDebug() << TAG << "parse len not enough";
        return false;
    }
    bool ok;
    /* CRC校验 */
    ProtUtils::parseCrc(buf, headIdx, protLen, ok);
    if(!ok){
        qDebug() << TAG << "parse crc error ";
        return false;
    }
    /* 解析各个字段 */
    buf.remove(0, headIdx + ProtPara::HEAD_LEN); //移除协议头
    ProtUtils::parseTimeStamp(buf, result.timeStamp);
    buf.remove(0, ProtPara::LEN_LEN); //移除数据长度
    ProtUtils::parseCmdType(buf, result.cmdType, ok);
    if(!ok){
        qDebug() << TAG << "parse cmd type error";
        return false;
    }
    ProtUtils::parseRgstAddr(buf, result.addr);
    ProtUtils::parseValue(buf, lenField - ProtPara::CMD_TYPE_LEN - ProtPara::ADDR_LEN, result.value);
    return true;
}

ProtContent ParseFsm::getResult()
{
    return result;
}
