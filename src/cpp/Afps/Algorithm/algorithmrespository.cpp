#include "algorithmrespository.h"

AlgorithmRespository::AlgorithmRespository(Baseline *baseline, Detection *detection, QObject *parent) :
    QObject(parent),
    baseline(baseline),
    detection(detection)
{

}

Baseline *AlgorithmRespository::getBaseline()
{
    return baseline;
}

Baseline::Para AlgorithmRespository::getBaselinePara()
{
    return baseline->mPara;
}

Detection::Para AlgorithmRespository::getDetectionPara()
{
    return detection->mPara;
}

Detection *AlgorithmRespository::getDetection()
{
    return detection;
}

void AlgorithmRespository::setBaselinePara(Baseline::Para para)
{
    qDebug() << "AlgorithmRespository::setBaselinePara " ;
    baseline->updatePara(para);
}

void AlgorithmRespository::setDetectionPara(Detection::Para para)
{
    detection->updatePara(para);
}
