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

QSerialPort::BaudRate SerialPortPara::getQtBaudrate()
{
    QSerialPort::BaudRate qtBaudRate;
    switch (baudrate) {
        case 9600:
            qtBaudRate = QSerialPort::BaudRate::Baud9600;
            break;
        case 115200:
            qtBaudRate = QSerialPort::BaudRate::Baud115200;
            break;
        default:
            qtBaudRate = QSerialPort::BaudRate::UnknownBaud;
            break;
    }
    return qtBaudRate;
}

QSerialPort::DataBits SerialPortPara::getQtDatabit()
{
    QSerialPort::DataBits qtDatabit;
    switch (databit) {
        case 5:
            qtDatabit = QSerialPort::DataBits::Data5;
            break;
        case 6:
            qtDatabit = QSerialPort::DataBits::Data6;
            break;
        case 7:
            qtDatabit = QSerialPort::DataBits::Data7;
            break;
        case 8:
            qtDatabit = QSerialPort::DataBits::Data8;
            break;
        default:
            qtDatabit = QSerialPort::DataBits::UnknownDataBits;
            break;
    }
    return qtDatabit;
}

QSerialPort::StopBits SerialPortPara::getQtStopbit()
{
    QSerialPort::StopBits qtStopbit;
    if(stopbit < static_cast<float>(1.1)){
        qtStopbit = QSerialPort::StopBits::OneStop;
    } else if(stopbit < static_cast<float>(1.9)){
        qtStopbit = QSerialPort::StopBits::OneAndHalfStop;
    } else {
        qtStopbit = QSerialPort::StopBits::TwoStop;
    }
    return qtStopbit;
}
