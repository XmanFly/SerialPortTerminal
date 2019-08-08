#ifndef RAWLOGTXT_H
#define RAWLOGTXT_H

#include <QObject>

class RawLogTxt : public QObject
{
    Q_OBJECT
    Q_PROPERTY(NOTIFY sig_add)
public:
    explicit RawLogTxt(QObject *parent = nullptr);

signals:
    void sig_add(QString data, int type);

public slots:
    void slot_receive(QByteArray );
    void slot_send(QByteArray );

private:
    void addData(QByteArray src, int type);
};

#endif // RAWLOGTXT_H
