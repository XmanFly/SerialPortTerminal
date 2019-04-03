#include "algorithmviewmodel.h"

AfpsAlgorithmViewModel::AfpsAlgorithmViewModel(QObject *parent) : QObject(parent)
{
    setResult("Ready");
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
    setDetectionTimeout(respository->getDetectionPara().timeout);
    setDetectionThrold(respository->getDetectionPara().throld);
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
    return detectionThrold;
}

void AfpsAlgorithmViewModel::setDetectionThrold(double detectionThrold)
{
    this->detectionThrold = detectionThrold;
    Detection::Para para = respository->getDetectionPara();
    para.throld = detectionThrold;
    respository->setDetectionPara(para);
    emit sig_detectionThrold();
}


