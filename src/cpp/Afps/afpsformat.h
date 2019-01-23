#ifndef AFPSFORMAT_H
#define AFPSFORMAT_H

#include "afpsprotpara.h"
#include "../ProtBasic/protformatbasic.h"

class AfpsFormat : public ProtFormatBasic<PROT_FIELD, QByteArray>
{
public:
    AfpsFormat();

    void getDevId(DEV_ID &dev, bool &ok);
};

#endif // AFPSFORMAT_H
