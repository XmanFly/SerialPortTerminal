#ifndef BASICDEV_H
#define BASICDEV_H


template <typename DEV_ID, class PROT>
class BasicDev
{
public:

    BasicDev(DEV_ID id) :
        id(id) {
    }

    //获取设备Id
    DEV_ID	getId(){
        return id;
    }

    virtual bool rcvProt(PROT prot) = 0;

protected:
    DEV_ID id; //设备id
    PROT prot; //协议数据
};

#endif // BASICDEV_H
