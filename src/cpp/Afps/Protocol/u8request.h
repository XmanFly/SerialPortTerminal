#ifndef U8REQUEST_H
#define U8REQUEST_H

#include <QObject>
#include "request.h"

class U8Request : public Request
{
    Q_OBJECT
public:
    explicit U8Request(Request::METHOD mMethod, uchar rgstAddr, quint8 setValue = 0, QObject *parent = nullptr);
    quint8 getReadValue() const;

private:
    quint8 setValue;
    quint8 readValue;
    QByteArray valueToRaw(quint8 value);
    bool parseRgstValue(ProtContent response);

signals:

public slots:
};

#endif // U8REQUEST_H
