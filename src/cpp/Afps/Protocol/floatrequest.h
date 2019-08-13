#ifndef FLOATREQUEST_H
#define FLOATREQUEST_H

#include <QObject>
#include "request.h"


class FloatRequest : public Request
{
    Q_OBJECT
public:
    explicit FloatRequest(Request::METHOD mMethod, uchar rgstAddr, float setValue = 0, float scale = 10, QObject *parent = nullptr);

    float getReadValue() const;

private:
    float setValue;
    float readValue;
    QByteArray valueToRaw(float value);
    bool parseRgstValue(ProtContent response);

signals:

public slots:
};

#endif // FLOATREQUEST_H
