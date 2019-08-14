#ifndef REGU8READVM_H
#define REGU8READVM_H

#include <QObject>
#include "regrequestvm.h"
#include "../Protocol/u8request.h"

class RegU8ReadVM : public RegRequestVM
{
    Q_OBJECT
    Q_PROPERTY(quint8 value READ getValue NOTIFY sig_valueChanged)
public:
    explicit RegU8ReadVM(Request::METHOD method, uchar addr, QObject *parent = nullptr);
    Q_INVOKABLE bool readSync(); //同步读取
    quint8 getValue();
    void setValue(quint8 value);

private:
    const QString TAG = "RegU8ReadVM";
    U8Request* request;
    quint8 value;

signals:
    void sig_valueChanged();

public slots:
};

#endif // REGU8READVM_H
