#ifndef AFPSPROTGEN_H
#define AFPSPROTGEN_H

#include <QByteArray>
#include "../ProtBasic/protgenbasic.h"
#include "afpsformat.h"

class AfpsProtGen : public ProtGenBasic<AfpsFormat, QByteArray>
{
public:
    AfpsProtGen();
    ~AfpsProtGen();

    QByteArray gen(char rgst, QByteArray content); //生成协议

private:
    void addHead();    
    void addLen();
    void addRegist(char rgst);
    void addContent(QByteArray content);
    void addCheckSum();
};

#endif // AFPSPROTGEN_H
