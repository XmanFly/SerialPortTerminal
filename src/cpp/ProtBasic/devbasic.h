#ifndef DEVBASIC_H
#define DEVBASIC_H

template <typename DEV_ID, class PROT_RCV, class PROT_GEN>
class DevBasic
{
public:
    DevBasic(DEV_ID id) :
        devId(id)
    {
    }

    //获取设备Id
    DEV_ID	getId(){
        return devId;
    }

    virtual bool rcvProt(PROT_RCV prot) = 0;
    virtual void parse() = 0; //解析协议内容

protected:
    DEV_ID devId; //设备id
    PROT_RCV protRcv; //接收协议数据
    PROT_GEN *protGen;
};

#endif // BASICDEV_H
