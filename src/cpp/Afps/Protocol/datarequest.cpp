#include "datarequest.h"

DataRequest::DataRequest(Request::METHOD mMethod, uchar rgstAddr, DataType type, float setValue, float scale, QObject *parent ) :
    Request(mMethod, rgstAddr, nullptr, parent)
{
    sendContent.value = value2ByteArray(type, static_cast<uint>(setValue/10));
}


QByteArray DataRequest::value2ByteArray(DataType type, uint src)
{
    QByteArray res;
    switch (type) {
    case U8:
        for (int i=0; i<1; i++) {
            res.append(static_cast<char>((src >> i) & 0xFF));
        }
        break;
    case U16:
        for (int i=0; i<2; i++) {
            res.append(static_cast<char>((src >> i) & 0xFF));
        }
        break;
    case Other:
        break;
    }
    return res;
}
