#ifndef PARSEFSM_H
#define PARSEFSM_H

#include <QObject>
#include "protpara.h"
#include "protcontent.h"
#include "protutils.h"

class ParseFsm
{
public:
    ParseFsm();
    ~ParseFsm();
    bool parse(QByteArray &buf);
    ProtContent getResult();

private:
    const QString TAG = "ParseFsm";
    ProtContent result;

signals:

public slots:
};

#endif // PARSEFSM_H
