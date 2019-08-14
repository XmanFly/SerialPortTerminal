#ifndef REGFLOATREADVM_H
#define REGFLOATREADVM_H

#include <QObject>
#include "regrequestvm.h"
#include "../Protocol/floatrequest.h"

class RegFloatReadVM : public RegRequestVM
{
    Q_OBJECT
    Q_PROPERTY(float value READ getValue NOTIFY sig_valueChanged)
public:
    explicit RegFloatReadVM(Request::METHOD method, uchar addr, QObject *parent = nullptr);
    Q_INVOKABLE bool readSync(); //同步读取
    float getValue();
    void setValue(float value);

private:
    const QString TAG = "RegFloatReadVM";
    FloatRequest* request;
    float value;

signals:
    void sig_valueChanged();

public slots:
};

#endif // REGFLOATREADVM_H
