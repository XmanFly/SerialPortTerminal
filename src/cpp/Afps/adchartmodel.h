#ifndef ADCHARTMODEL_H
#define ADCHARTMODEL_H

#include <QObject>
#include <QDebug>
#include <QPointF>
#include <QThread>
#include "adchanneldev.h"

//坐标轴范围
struct AxisRange{
    Q_GADGET
public:
    double xMin;
    double xMax;
    double yMin;
    double yMax;
    Q_PROPERTY(double xMin MEMBER xMin)
    Q_PROPERTY(double xMax MEMBER xMax)
    Q_PROPERTY(double yMin MEMBER yMin)
    Q_PROPERTY(double yMax MEMBER yMax)

    AxisRange(){
        this->xMin = 0;
        this->xMax = 0;
        this->yMin = 0;
        this->yMax = 0;
    }

    AxisRange(double xMin, double xMax, double yMin, double yMax){
        this->xMin = xMin;
        this->xMax = xMax;
        this->yMin = yMin;
        this->yMax = yMax;
    }

    void clear(){
        this->xMin = 0;
        this->xMax = 0;
        this->yMin = 0;
        this->yMax = 0;
    }

    AxisRange & operator=(const AxisRange &src){
        this->xMin = src.xMin;
        this->xMax = src.xMax;
        this->yMin = src.yMin;
        this->yMax = src.yMax;
        return *this;
    }

    friend QDebug operator<<(QDebug stream, const AxisRange &src) {
        stream << QString("%1 %2 %3 %4 ").arg(src.xMin).arg(src.xMax)
                  .arg(src.yMin).arg(src.yMax);
        return stream;
    }

    bool operator!=(const AxisRange &src) const{
        Q_UNUSED(src)
        return true;
    }

};
Q_DECLARE_METATYPE(AxisRange);


class AdChartModel : public QObject
{
    Q_OBJECT
public:
    explicit AdChartModel(QObject *parent = nullptr);

    QVector<QVector<QPointF> *> channel; //通道数值
    QVector<AxisRange > channelRange; //每个通道数值范围
    void clear();

private:
    bool isWork;
    void calcRange(); //计算每个通道数值范围
    void dataChanged();

signals:
    void sig_ch1Data(QVector<QPointF> mData, AxisRange mAxisRange);
    void sig_ch2Data(QVector<QPointF> mData, AxisRange mAxisRange);
    void sig_ch3Data(QVector<QPointF> mData, AxisRange mAxisRange);
    void sig_ch4Data(QVector<QPointF> mData, AxisRange mAxisRange);

public slots:    
    void slot_ctrl(bool isStart);
    void slot_rcvData(AD_CHANNEDL_DATA data);
    void slot_rcvAllData(QVector<QVector<QPointF> > data); //收到单次采样所有数据
};

#endif // ADCHARTMODEL_H
