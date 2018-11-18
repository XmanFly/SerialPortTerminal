#ifndef SERIALPORTPARA_H
#define SERIALPORTPARA_H

#include <QObject>
#include <QSerialPort>

/* 串口参数 */
class SerialPortPara : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString number READ getNumber WRITE setNumber)
    Q_PROPERTY(qint32 baudrate READ getBaudrate WRITE setBaudrate)
    Q_PROPERTY(qint32 databit READ getDatabit WRITE setDatabit)
    Q_PROPERTY(float stopbit READ getStopbit WRITE setStopbit)

public:
    explicit SerialPortPara(QObject *parent = nullptr);

    QString getNumber();
    void	setNumber(QString number);
    qint32	getBaudrate();
    void	setBaudrate(qint32 baudrate);
    qint32	getDatabit();
    void	setDatabit(qint32 databit);
    float	getStopbit();
    void	setStopbit(float stopbit);

public:
    //QT专用格式
    QSerialPort::BaudRate getQtBaudrate();
    QSerialPort::DataBits getQtDatabit();
    QSerialPort::StopBits getQtStopbit();

private:
    QString number; //串口号
    qint32	baudrate; //波特率
    qint32	databit; //数据位
    float	stopbit; //停止位

signals:

public slots:

};

#endif // SERIALPORTPARA_H
