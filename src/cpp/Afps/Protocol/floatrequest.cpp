#include "floatrequest.h"

FloatRequest::FloatRequest(Request::METHOD mMethod, uchar rgstAddr, float setValue, float scale, QObject *parent) :
    Request(mMethod, rgstAddr, nullptr, parent),
    scale(scale)
{
    if(mMethod == Request::SET){
        sendContent.value = valueToRaw(setValue*scale);
    }
}

float FloatRequest::getReadValue() const
{
    return readValue;
}

QByteArray FloatRequest::valueToRaw(float value)
{
    QByteArray res;
    ushort tmp = static_cast<ushort>(value);
    res.append(static_cast<char>(tmp&0xFF));
    res.append(static_cast<char>((tmp>>8)&0xFF));
    return res;
}

bool FloatRequest::parseRgstValue()
{
    if(receiveContent.value.size() != 2){
        return false;
    }
    readValue = ((receiveContent.value.at(0) & 0xFF) |
                    ((receiveContent.value.at(1) & 0xFF) << 8)) / scale;
    return true;
}
