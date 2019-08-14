#include "u8request.h"

U8Request::U8Request(Request::METHOD mMethod, uchar rgstAddr, quint8 setValue, QObject *parent) :
    Request(mMethod, rgstAddr, nullptr, parent)
{
    sendContent.value = valueToRaw(setValue);
}

quint8 U8Request::getReadValue() const
{
    return readValue;
}

QByteArray U8Request::valueToRaw(quint8 value)
{
    QByteArray res;
    res.append(static_cast<char>(value));
    return res;
}

bool U8Request::parseRgstValue(ProtContent response)
{
    this->receiveContent = response;
    if(receiveContent.value.size() != 1){
        return false;
    }
    readValue = static_cast<quint8>(receiveContent.value.at(0));
    return true;
}
