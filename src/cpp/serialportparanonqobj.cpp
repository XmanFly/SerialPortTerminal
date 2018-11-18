#include "serialportparanonqobj.h"

SerialPortParaNonQobj::SerialPortParaNonQobj()
{

}

SerialPortParaNonQobj::SerialPortParaNonQobj(SerialPortPara &mSerialPortPara)
{
    this->number = mSerialPortPara.getNumber();
    this->baudrate = mSerialPortPara.getQtBaudrate();
    this->databit = mSerialPortPara.getQtDatabit();
    this->stopbit = mSerialPortPara.getQtStopbit();
}




