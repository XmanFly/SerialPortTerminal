#ifndef PROTGENBASIC_H
#define PROTGENBASIC_H

template <class PROT_FORMAT, typename R >

class ProtGenBasic
{
public:
    ProtGenBasic(){}

    virtual ~ProtGenBasic(){

    }

    PROT_FORMAT prot; //生成的协议内容
};

#endif // PROTGENBASIC_H
