#ifndef DETECTION_H
#define DETECTION_H

#include <QObject>
#include <QDebug>

/* 检测期  */
class Detection : public QObject
{
    Q_OBJECT
public:

    struct Para {
        int windowLen; //检测窗口长度
        int timeout; //超时长度
        double standard; //基准
        double throld; //判定阈值
        Para(int windowLen, int timeout, double standard, double throld) {
            this->windowLen = windowLen;
            this->timeout = timeout;
            this->standard = standard;
            this->throld = throld;
        }
    };

    explicit Detection(Para mPara, QObject *parent = nullptr);

    int points; //累计点数
    bool isDectected; //检出标志
    bool isTimeout;
    Para mPara; //参数

    void init();
    void process(double data); //物质判定

};

#endif // DETECTION_H
