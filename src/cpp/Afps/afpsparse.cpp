#include "afpsparse.h"

AfpsParse::AfpsParse()
{

}

void AfpsParse::parse(QByteArray &buf, AfpsFormat &mProtResult)
{
    //置为未解出协议
    mProtResult.setIsValid(false);
    //协议头
    QByteArray head;
    head.append(static_cast<char>(ProtPara::CMD_HEAD));
    //查找协议头
    int headIdx = buf.indexOf(head);
    if(headIdx == -1){
        return;
    }
    //是否包含长度字段
    if(buf.size() < (headIdx+2)){
        return;
    }
    char len = buf.at(headIdx+1);
    //查看协议是否完整
    if(buf.size() < (len+headIdx)){
        return;
    }
    //检查校验码
    QByteArray checksum;
//    if((checksum.at(0) != buf.at(headIdx+len-2)) || (checksum.at(1) != buf.at(headIdx+len-1))){
//        //从buffer中删除此协议头及之前内容
//        buf.remove(0, headIdx+2);
//        return;
//    }
    //填充解析结果
    mProtResult.addInfor(PROT_FIELD::HEAD, buf.mid(headIdx, 1));
    mProtResult.addInfor(PROT_FIELD::LEN, buf.mid(headIdx + 1, 1));
    mProtResult.addInfor(PROT_FIELD::REGIST, buf.mid(headIdx + 2, 1));
    mProtResult.addInfor(PROT_FIELD::CONTENT, buf.mid(headIdx + 3, len-4));
    mProtResult.addInfor(PROT_FIELD::CHECK_SUM, buf.mid(headIdx + len - 1, 1));
    mProtResult.setIsValid(true);
    //从buffer删除此协议及之前内容
    buf.remove(0, headIdx+len);
    return;
}
