#include "singleaccuchartmodel.h"


SingleAccuChartModel::SingleAccuChartModel(int dispSize, QObject *parent) :
    QObject(parent),
    dispSize(dispSize)
{
    m_lineData = new QVector<QPointF>();
}

void SingleAccuChartModel::slot_receiveData(double mData)
{
    qDebug() << TAG << "receive data" << mData;
    if(m_lineData->size() >= dispSize ){
        m_lineData->removeFirst();
        //调整前面的数据位置
        for(int i=0; i<m_lineData->size(); i++) {
            (*m_lineData)[i].setX(i+1);
        }
    }
    m_lineData->append(QPointF(m_lineData->size()+1, mData));
    /*检索最大最小值*/
    AxisRange axisRange;
    axisRange.xMin = 0;
    axisRange.xMax = dispSize;
    axisRange.yMin = 1e10;
    axisRange.yMax = -1e10;
    foreach(QPointF each, *m_lineData){
        if(each.y() < axisRange.yMin){
            axisRange.yMin = each.y();
        }
        if(each.y() > axisRange.yMax){
            axisRange.yMax = each.y();
        }
    }
    emit sig_data(*m_lineData, axisRange);
}

