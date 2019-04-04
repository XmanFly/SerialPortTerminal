#include "algorithmviewmodel.h"

AfpsAlgorithmViewModel::AfpsAlgorithmViewModel(QObject *parent) : QObject(parent)
{
    setResult("");
}

void AfpsAlgorithmViewModel::setRespository(AlgorithmRespository *respository)
{
    this->respository = respository;
    loadPara();
}


void AfpsAlgorithmViewModel::loadPara()
{
    setBaselineWin(respository->getBaselinePara().windowLen);
    setBaselineThrold(respository->getBaselinePara().stableThrold);
    setBaselineStandard(respository->getBaseline()->standard);
    setDetectionTimeout(respository->getDetectionPara().timeout);
    setDetectionThrold(respository->getDetectionPara().throld * 100);
    setDetectionDiff(respository->getDetection()->diff);
    setDetectionFallRate(respository->getDetection()->fallRate);
}

QString AfpsAlgorithmViewModel::getResult()
{
    return result;
}

void AfpsAlgorithmViewModel::setResult(QString result)
{
    if(this->result != result){
        this->result = result;
        emit sig_resultChanged();
    }
}

void AfpsAlgorithmViewModel::slot_updateResult(QString result)
{
    setResult(result);
}

int AfpsAlgorithmViewModel::getBaselineWin()
{
    return baselineWin;
}

void AfpsAlgorithmViewModel::setBaselineWin(int baselineWin)
{
    qDebug() << "AfpsAlgorithmViewModel::setBaselineWin " << baselineWin;
    if(baselineWin < 100 && baselineWin > 0){
        this->baselineWin = baselineWin;
        Baseline::Para para = respository->getBaselinePara();
        para.windowLen = baselineWin;
        respository->setBaselinePara(para);
    }
    emit sig_baselineWin();
}

void AfpsAlgorithmViewModel::slot_updateBaselineWin(int baselineWin)
{
    setBaselineWin(baselineWin);
}

double AfpsAlgorithmViewModel::getBaselineThrold()
{
    return baselineThrold;
}

void AfpsAlgorithmViewModel::setBaselineThrold(double baselineThrold)
{
    this->baselineThrold = baselineThrold;
    Baseline::Para para = respository->getBaselinePara();
    para.stableThrold = baselineThrold;
    respository->setBaselinePara(para);
    emit sig_baselineThrold();
}

void AfpsAlgorithmViewModel::slot_updateBaseThrold(int baselineThrold)
{
    setBaselineThrold(baselineThrold);
}

double AfpsAlgorithmViewModel::getBaselineStandard()
{
    return baselineStandard;
}

void AfpsAlgorithmViewModel::setBaselineStandard(double baselineStandard)
{
    this->baselineStandard = baselineStandard;
    emit sig_baselineStandard();
}

int AfpsAlgorithmViewModel::getDetectionTimeout()
{
    return detectionTimeout;
}

void AfpsAlgorithmViewModel::setDetectionTimeout(int detectionTimeout)
{
    this->detectionTimeout = detectionTimeout;
    Detection::Para para = respository->getDetectionPara();
    para.timeout = detectionTimeout;
    respository->setDetectionPara(para);
    emit sig_detectionTimeout();
}

double AfpsAlgorithmViewModel::getDetectionThrold()
{
    return detectionThrold * 100;
}

void AfpsAlgorithmViewModel::setDetectionThrold(double detectionThrold)
{
    this->detectionThrold = detectionThrold / 100;
    Detection::Para para = respository->getDetectionPara();
    para.throld = this->detectionThrold;
    respository->setDetectionPara(para);
    emit sig_detectionThrold();
}

double AfpsAlgorithmViewModel::getDetectionDiff()
{
    return detectionDiff;
}

void AfpsAlgorithmViewModel::setDetectionDiff(double detectionDiff)
{
    this->detectionDiff = detectionDiff;
    emit sig_detectionDiff();
}

double AfpsAlgorithmViewModel::getDetectionFallRate()
{
    return fallRate * 100;
}

void AfpsAlgorithmViewModel::setDetectionFallRate(double detectionFallRate)
{
    this->fallRate = detectionFallRate;
    emit sig_detectionFallRate();
}

QString AfpsAlgorithmViewModel::getState()
{
    return state;
}

void AfpsAlgorithmViewModel::setState(QString state)
{
    this->state = state;
    emit sig_state();
}

void AfpsAlgorithmViewModel::slot_updateState(QString state)
{
    setState(state);
}

void AfpsAlgorithmViewModel::slot_updateStandard()
{
//    qDebug() << "AfpsAlgorithmViewModel::slot_updateStandard ";
    setBaselineStandard(respository->getBaseline()->standard);
}


void AfpsAlgorithmViewModel::slot_updateDetectionDiff()
{
    setDetectionDiff(respository->getDetection()->diff);
}

void AfpsAlgorithmViewModel::slot_updateDetectionFallRate()
{
    setDetectionFallRate(respository->getDetection()->fallRate);
}


