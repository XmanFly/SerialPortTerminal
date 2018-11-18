#include "serialportpara.h"

SerialPortPara::SerialPortPara(QObject *parent) : QObject(parent)
{

}

QString SerialPortPara::getNumber()
{
    return number;
}

void SerialPortPara::setNumber(QString number)
{
    this->number = number;
}

qint32 SerialPortPara::getBaudrate()
{
    return baudrate;
}

void SerialPortPara::setBaudrate(qint32 baudrate)
{
    this->baudrate = baudrate;
}

qint32 SerialPortPara::getDatabit()
{
    return databit;
}

void SerialPortPara::setDatabit(qint32 databit)
{
    this->databit = databit;
}

float SerialPortPara::getStopbit()
{
    return stopbit;
}

void SerialPortPara::setStopbit(float stopbit)
{
    this->stopbit = stopbit;
}

