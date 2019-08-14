#ifndef REGU8WRITEVM_H
#define REGU8WRITEVM_H

#include <QObject>
#include "regrequestvm.h"
#include "../Protocol/u8request.h"

class RegU8WriteVM : public RegRequestVM
{
    Q_OBJECT
public:
    explicit RegU8WriteVM(Request::METHOD method, uchar addr, QObject *parent = nullptr);
    Q_INVOKABLE bool writeSync(quint8 value); //同步设置

private:
    const QString TAG = "RegFloatWriteVM";
    U8Request* request;

signals:

public slots:
};

#endif // REGU8WRITEVM_H
