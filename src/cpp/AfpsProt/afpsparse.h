#ifndef AFPSPARSE_H
#define AFPSPARSE_H

#include "../ProtBasic/parsebasic.h"
#include "../ProtBasic/protformatbasic.h"
#include "../ProtBasic/protpara.h"

class AfpsParse : public ParseBasic<QByteArray,  ProtFormatBasic<PROT_FIELD, QByteArray>>
{
public:
    AfpsParse();

    void parse(QByteArray &buf, ProtFormatBasic<PROT_FIELD, QByteArray> &mProtResult);

};

#endif // AFPSPARSE_H
