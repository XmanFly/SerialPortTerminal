#ifndef AFPSPARSE_H
#define AFPSPARSE_H

#include "afpsformat.h"
#include "../ProtBasic/parsebasic.h"
#include "../ProtBasic/protpara.h"

class AfpsParse : public ParseBasic<QByteArray,  AfpsFormat>
{
public:
    AfpsParse();

    void parse(QByteArray &buf, AfpsFormat &mProtResult);

};

#endif // AFPSPARSE_H
