#include "afpsprotgen.h"

AfpsProtGen::AfpsProtGen()
{

}

AfpsProtGen::~AfpsProtGen()
{

}

void AfpsProtGen::addHead()
{
    QByteArray head;
    head.append(static_cast<char>(AfpsProtPara::CMD_HEAD));
    prot.addInfor(PROT_FIELD::HEAD, head);
}

void AfpsProtGen::addRegist(char rgst)
{
    QByteArray rgstByte;
    rgstByte.append(rgst);
    prot.addInfor(PROT_FIELD::REGIST, rgstByte);
}

void AfpsProtGen::addLen()
{
    QByteArray lenByte;
    lenByte.append(static_cast<char>(prot.getInfor(PROT_FIELD::CONTENT).size()));
    prot.addInfor(PROT_FIELD::LEN, lenByte);
}

void AfpsProtGen::addContent(QByteArray content)
{
    prot.addInfor(PROT_FIELD::CONTENT, content);
}

void AfpsProtGen::addCheckSum()
{
//    QByteArray checkData;
//    checkData = prot.getInfor(PROT_FIELD::HEAD) + prot.getInfor(PROT_FIELD::LEN)
//            + prot.getInfor(PROT_FIELD::CTRL) + prot.getInfor(PROT_FIELD::CONTENT) ;
//    QByteArray checkSum = CRC16::gen(checkData);
    QByteArray checkSum;
    checkSum.append(0xCC);
    prot.addInfor(PROT_FIELD::CHECK_SUM, checkSum);
}

QByteArray AfpsProtGen::gen(char rgst, QByteArray content)
{
    prot.clear();
    addHead();
    addRegist(rgst);
    addContent(content);
    addLen();
    addCheckSum();
    QByteArray protData;
    protData = prot.getInfor(PROT_FIELD::HEAD) + prot.getInfor(PROT_FIELD::LEN)
            + prot.getInfor(PROT_FIELD::REGIST)  + prot.getInfor(PROT_FIELD::CONTENT)
            + prot.getInfor(PROT_FIELD::CHECK_SUM);
    return protData;
}
