#ifndef REGWRITEVM_H
#define REGWRITEVM_H

#include <QObject>
#include "regrequestvm.h"
#include "../Protocol/floatrequest.h"

class RegFloatWriteVM : public RegRequestVM
{
    Q_OBJECT
public:
    explicit RegFloatWriteVM(Request::METHOD method, uchar addr, QObject *parent = nullptr);
    Q_INVOKABLE bool writeSync(float value); //同步设置

private:
    const QString TAG = "RegFloatWriteVM";
    FloatRequest* request;

signals:

public slots:
};

#endif // REGWRITEVM_H
