#ifndef REGFLOATVM_H
#define REGFLOATVM_H

#include <QObject>
#include "../Protocol/wmvolley.h"
#include "../Protocol/request.h"

class RegRequestVM : public QObject
{
    Q_OBJECT
    Q_PROPERTY(RequestStyle::STATE state READ getState NOTIFY sig_stateChanged)
    Q_PROPERTY(QString dbgMsg READ getDbgMsg NOTIFY sig_dbgMsgChanged)
public:
    explicit RegRequestVM(Request::METHOD method, uchar addr, QObject *parent = nullptr);
    RequestStyle::STATE getState() const;
    QString getDbgMsg() const;

protected:
    Request* requestBase;
    Request::METHOD method;
    uchar addr;
    RequestStyle::STATE state;
    QString dbgMsg;

signals:
    void sig_valueChanged();
    void sig_stateChanged();
    void sig_dbgMsgChanged();

public slots:
    void slot_stateChanged();
};

#endif // REGFLOATVM_H
