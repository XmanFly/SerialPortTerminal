#ifndef AFPSFORMAT_H
#define AFPSFORMAT_H

#include "../ProtBasic/protformatbasic.h"
#include "../ProtBasic/protpara.h"

class AfpsFormat : public ProtFormatBasic<PROT_FIELD, QByteArray>
{
public:
    AfpsFormat();

    DEV_ID getDevId();
};

#endif // AFPSFORMAT_H
