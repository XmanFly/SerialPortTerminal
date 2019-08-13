#ifndef DATAREQUEST_H
#define DATAREQUEST_H

#include <QObject>
#include "request.h"


/* 数据类型请求 */
class DataRequest : public Request
{
    Q_OBJECT
public:
    //数据类型
    enum DataType {
        U16 = 0,
        U8 = 1,
        Other = 2,
    };
    explicit DataRequest(Request::METHOD mMethod, uchar rgstAddr, DataType type, float setValue, float scale, QObject *parent = nullptr);

private:
    QByteArray value2ByteArray(DataType type, uint src);

signals:

public slots:
};

#endif // DATAREQUEST_H
